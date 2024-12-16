/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_process_words.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:50:16 by hanjkim           #+#    #+#             */
/*   Updated: 2024/12/16 20:52:55 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*process_operator(char *input, int *i, int *start, t_data *data)
{
	t_token		*token;
	t_segment	*seg;

	token = create_empty_token();
	if (!token)
		return (NULL);
	seg = create_segment(false, false);
	if (!seg)
		return ((free_tokens(data), NULL));
	if ((input[*i] == '<' && input[*i + 1] == '<')
		|| (input[*i] == '>' && input[*i + 1] == '>'))
	{
		if (append_char_to_segment(seg, input[*i]) == -1
			|| append_char_to_segment(seg, input[*i + 1]) == -1)
			return ((free_segment(&seg), free_tokens(data), NULL));
		*i += 2;
	}
	else
	{
		if (append_char_to_segment(seg, input[*i]) == -1)
			return ((free_segment(&seg), free_tokens(data), NULL));
		(*i)++;
	}
	add_segment_to_token(token, seg);
	*start = *i;
	return (token);
}

static int	process_quoted_segment(char *input, int *i, t_token *token,
	bool single_quote)
{
	char		quote_char;
	t_segment	*seg;

	if (single_quote)
		quote_char = '\'';
	else
		quote_char = '"';
	seg = create_segment(single_quote, !single_quote);
	if (!seg)
		return (-1);
	(*i)++;
	while (input[*i] && input[*i] != quote_char)
	{
		if (append_char_to_segment(seg, input[*i]) == -1)
			return (free(seg->text), free(seg), -1);
		(*i)++;
	}
	if (input[*i] == quote_char)
		(*i)++;
	else
		return (free(seg->text), free(seg), -1);
	add_segment_to_token(token, seg);
	return (0);
}

static int	process_unquoted_chars(char *input, int *i, t_token *token)
{
	t_segment	*seg;

	seg = create_segment(false, false);
	if (!seg)
		return (-1);
	while (input[*i] && input[*i] != ' ' && input[*i] != '\t'
		&& input[*i] != '\'' && input[*i] != '"')
	{
		if (input[*i] == '\\' && input[*i + 1])
		{
			(*i)++;
			if (append_char_to_segment(seg, input[*i]) == -1)
				return (free(seg->text), free(seg), -1);
			(*i)++;
			continue ;
		}
		if (append_char_to_segment(seg, input[*i]) == -1)
			return (free(seg->text), free(seg), -1);
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
	while (input[i] && input[i] != ' ' && input[i] != '\t'
		&& input[i] != '<' && input[i] != '>' && input[i] != '|')
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
