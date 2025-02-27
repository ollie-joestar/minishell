/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 20:03:14 by hanjkim           #+#    #+#             */
/*   Updated: 2025/02/27 15:17:35 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	should_split_token(t_token *token)
{
	t_segment	*seg;
	bool		any_unquoted;
	bool		contains_space;

	any_unquoted = false;
	contains_space = false;
	if (token->type != WORD)
		return (false);
	seg = token->segments;
	while (seg)
	{
		if (!seg->single_quoted && !seg->double_quoted)
		{
			any_unquoted = true;
			if (ft_strchr(seg->text, ' ') || ft_strchr(seg->text, '\t')
				|| ft_strchr(seg->text, '\r') || ft_strchr(seg->text, '\v')
				|| ft_strchr(seg->text, '\f'))
				contains_space = true;
		}
		seg = seg->next;
	}
	return (any_unquoted && contains_space);
}

t_token	*create_token_for_string(char *str)
{
	t_token		*new_token;
	t_segment	*seg;

	new_token = create_empty_token();
	if (!new_token)
		return (NULL);
	seg = create_segment(false, false);
	if (!seg)
		return (free(new_token), NULL);
	ft_free(&seg->text);
	seg->text = ft_strdup(str);
	if (!seg->text)
		return (free(seg), free(new_token), NULL);
	add_segment_to_token(new_token, seg);
	return (new_token);
}

t_token	*make_split_tokens(char **words, t_data *data, int i)
{
	t_token	*first_token;
	t_token	*last_token;
	t_token	*new_token;

	first_token = NULL;
	last_token = NULL;
	while (words[++i] != NULL)
	{
		new_token = create_token_for_string(words[i]);
		if (!new_token)
			((free_arr(&words), free_tokens(data), bruh(data, "Oh", 2)));
		new_token->type = WORD;
		if (!first_token)
		{
			first_token = new_token;
			last_token = new_token;
		}
		else
		{
			last_token->next = new_token;
			new_token->prev = last_token;
			last_token = new_token;
		}
	}
	return (first_token);
}

t_token	*split_token(t_token *original_token, t_data *data)
{
	char			*joined;
	char			**words;
	t_token			*new_tokens;
	int				i;

	i = -1;
	joined = join_segments(original_token);
	if (!joined)
		bruh(data, "Failed to join token segments", 2);
	words = ft_split_set(joined, " \t\n\r\v\f");
	ft_free(&joined);
	if (!words)
		bruh(data, "Failed to split token words", 2);
	new_tokens = make_split_tokens(words, data, i);
	free_arr(&words);
	return (new_tokens);
}
