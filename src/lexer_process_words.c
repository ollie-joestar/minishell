/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_process_words.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:50:16 by hanjkim           #+#    #+#             */
/*   Updated: 2025/03/05 15:41:48 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Process a quoted segment (either SQ or DQ)
int	process_quoted_segment(char *input, int *i, t_token *token,
	bool single_quote)
{
	char		quote_char;
	int			seg_start;
	char		*quoted_text;
	t_segment	*seg;

	(*i)++;
	seg_start = *i;
	if (single_quote)
		quote_char = '\'';
	else
		quote_char = '\"';
	while (input[*i] && input[*i] != quote_char)
		(*i)++;
	quoted_text = ft_substr(input, seg_start, *i - seg_start);
	if (!quoted_text)
		return (0);
	seg = create_segment(single_quote, !single_quote);
	if (!seg)
		return (ft_free(&quoted_text), 0);
	seg->text = quoted_text;
	add_segment_to_token(token, seg);
	(*i)++;
	return (1);
}

// Process segment free of quotes
int	process_unquoted_segment(char *input, int *i, t_token *token)
{
	int			seg_start;
	char		*quoted_text;
	t_segment	*seg;

	seg_start = *i;
	while (input[*i] && !ft_strchr(" \t<>|'\"", input[*i]))
		(*i)++;
	quoted_text = ft_substr(input, seg_start, *i - seg_start);
	if (!quoted_text)
		return (0);
	seg = create_segment(false, false);
	if (!seg)
		return (ft_free(&quoted_text), free_segment(&token->segments), 0);
	seg->text = quoted_text;
	add_segment_to_token(token, seg);
	return (1);
}

// Inspect the input and create a token based on the input checks
t_token	*parse_word_token(char *input, int *start, t_data *data)
{
	t_token	*token;
	int		i;
	int		res;

	i = *start;
	if (ft_strchr("<>|", input[i]))
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
		if (res == 0)
			return (free_tokens(data), NULL);
	}
	return (*start = i, token);
}
