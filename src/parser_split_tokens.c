/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 20:03:14 by hanjkim           #+#    #+#             */
/*   Updated: 2025/02/11 17:17:08 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_split_vars(t_split_vars *vars)
{
	vars->words = NULL;
	vars->new_head = NULL;
	vars->new_tail = NULL;
	vars->new_token = NULL;
	vars->i = -1;
}

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
			if (ft_strchr(seg->text, ' ') || ft_strchr(seg->text, '\t') ||
				ft_strchr(seg->text, '\r') || ft_strchr(seg->text, '\v') ||
				ft_strchr(seg->text, '\f'))
				contains_space = true;
		}
		seg = seg->next;
	}
	return (any_unquoted && contains_space);
}

t_token	*create_token_from_string(char *str)
{
	t_token		*new_token;
	t_segment	*seg;

	new_token = create_empty_token();
	if (!new_token)
		return (NULL);
	seg = create_segment(false, false);
	if (!seg)
		return (free(new_token), NULL);
	free(seg->text);
	seg->text = ft_strdup(str);
	if (!seg->text)
	{
		free(seg);
		free(new_token);
		return (NULL);
	}
	add_segment_to_token(new_token, seg);
	return (new_token);
}

void	make_split_tokens(t_split_vars *vars, t_token *original, t_data *data)
{
	t_token	*new_token;

	(void)original;
	while (vars->words[++vars->i] != NULL)
	{
		new_token = create_token_from_string(vars->words[vars->i]);
		if (!new_token)
		{
			free_arr(&vars->words);
			bruh(data, "Split_tok fail", 2);
		}
		new_token->type = WORD;
		if (!vars->new_head)
		{
			vars->new_head = new_token;
			vars->new_tail = new_token;
		}
		else
		{
			vars->new_tail->next = new_token;
			new_token->prev = vars->new_tail;
			vars->new_tail = new_token;
		}
	}
}

t_token	*split_token(t_token *original_token, t_data *data)
{
	t_split_vars	vars;
	char			*joined;

	init_split_vars(&vars);
	joined = join_segments(original_token);
	if (!joined)
		bruh(data, "Failed to join token segments", 2);
	vars.words = ft_split_set(joined, " \t\n\r\v\f");
	ft_free(&joined);
	if (!vars.words)
		bruh(data, "Failed to split token words", 2);
	make_split_tokens(&vars, original_token, data);
	free_arr(&vars.words);
	return (vars.new_head);
}
