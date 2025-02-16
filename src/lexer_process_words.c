/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_process_words.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:50:16 by hanjkim           #+#    #+#             */
/*   Updated: 2025/02/16 17:36:48 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_quoted_segment(char *input, int *i, t_token *token,
	bool single_quote)
{
	char		quote_char;
	t_segment	*seg;

	if (single_quote)
		quote_char = '\'';
	else
		quote_char = '\"';
	seg = create_segment(single_quote, !single_quote);
	if (!seg)
		return (-1);
	(*i)++;
	while (input[*i] && input[*i] != quote_char)
	{
		if (append_char_to_segment(seg, input[*i]) == -1)
			return (ft_free(&seg->text), free(seg), -1);
		(*i)++;
	}
	if (input[*i] == quote_char)
		(*i)++;
	else
		return (ft_free(&seg->text), free(seg), -1);
	add_segment_to_token(token, seg);
	return (0);
}

static int	process_unquoted_chars(char *input, int *i, t_token *token)
{
	t_segment	*seg;

	seg = create_segment(false, false);
	if (!seg)
		return (-1);
	while (input[*i] && !ft_strchr(" \t<>|'\"", input[*i]))
	{
		if (input[*i] == '\\' && input[*i + 1])
		{
			(*i)++;
			if (append_char_to_segment(seg, input[*i]) == -1)
				return (ft_free(&seg->text), free(seg), -1);
			(*i)++;
			continue ;
		}
		if (append_char_to_segment(seg, input[*i]) == -1)
			return (ft_free(&seg->text), free(seg), -1);
		(*i)++;
	}
	add_segment_to_token(token, seg);
	return (0);
}

t_token	*parse_word_token(char *input, int *start, t_data *data)
{
	t_token	*token;
	int		i;
	int		res;

	i = *start;
	if (input[i] == '<' || input[i] == '>' || input[i] == '|')
		return (process_operator(input, &i, start, data));
	token = create_empty_token();
	if (!token)
		return (NULL);
	while (input[i] && !ft_strchr(" \t<>|", input[i]))
	{
		if (input[i] == SQ)
			res = process_quoted_segment(input, &i, token, true);
		else if (input[i] == DQ)
			res = process_quoted_segment(input, &i, token, false);
		else
			res = process_unquoted_chars(input, &i, token);
		if (res == -1)
			return (free_tokens(data), NULL);
	}
	*start = i;
	return (token);
}
