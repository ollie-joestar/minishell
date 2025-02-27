/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 20:03:14 by hanjkim           #+#    #+#             */
/*   Updated: 2025/02/27 19:03:25 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Check if the token should be split based on quotation
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

// Create a token for the new string
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

// Append the new token to the end of the token list
void	append_token(t_token **first, t_token **last, t_token *new_token)
{
	if (!*first)
	{
		*first = new_token;
		*last = new_token;
	}
	else
	{
		(*last)->next = new_token;
		new_token->prev = *last;
		*last = new_token;
	}
}

//Make a new token for each word in the split string
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
			((free_token_node(&first_token),
					free_arr(&words), bruh(data, "Oh", 2)));
		new_token->type = WORD;
		append_token(&first_token, &last_token, new_token);
	}
	return (first_token);
}

// Split the token into multiple tokens
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
