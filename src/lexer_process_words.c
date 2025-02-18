/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_process_words.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:50:16 by hanjkim           #+#    #+#             */
/*   Updated: 2025/02/18 16:26:02 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int process_quoted_segment(char *input, int *i, t_token *token,
	bool single_quote)
{
	char quote_char;
	int start;
	char *segment_str;
	t_segment *seg;

	(*i)++;
	start = *i;
	if (single_quote)
		quote_char = '\'';
	else
		quote_char = '\"';
	while (input[*i] && input[*i] != quote_char)
		(*i)++;
	segment_str = ft_substr(input, start, *i - start);
	if (!segment_str)
		return (-1);
	seg = create_segment(single_quote, !single_quote);
	if (!seg)
		return (ft_free(&segment_str), -1);
	ft_free(&seg->text);
	seg->text = segment_str;
	add_segment_to_token(token, seg);
	(*i)++;
	return (0);
}


static int process_unquoted_segment(char *input, int *i, t_token *token)
{
	int start;
	char *segment_str;
	t_segment *seg;

	start = *i;
	while (input[*i] && !ft_strchr(" \t<>|'\"", input[*i]))
		(*i)++;
	segment_str = ft_substr(input, start, *i - start);
	if (!segment_str)
		return (-1);
	seg = create_segment(false, false);
	if (!seg)
		return (ft_free(&segment_str), free_segment(&token->segments), -1);
	ft_free(&seg->text);
	seg->text = segment_str;
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
			res = process_unquoted_segment(input, &i, token);
		if (res == -1)
			return (free_tokens(data), NULL);
	}
	*start = i;
	return (token);
}
