/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_process_words.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:50:16 by hanjkim           #+#    #+#             */
/*   Updated: 2024/12/08 18:37:44 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_segment	*create_segment(bool single_quoted, bool double_quoted)
{
	t_segment	*seg;

	seg = ft_calloc(1, sizeof(t_segment));
	if (!seg)
		return (NULL);
	seg->text = ft_calloc(1, sizeof(char));
	if (!seg->text)
		return (free(seg), NULL);
	seg->single_quoted = single_quoted;
	seg->double_quoted = double_quoted;
	seg->next = NULL;
	return (seg);
}

static int	append_char_to_segment(t_segment *seg, char c)
{
	size_t	old_len;
	char	*new_text;

	old_len = ft_strlen(seg->text);
	new_text = ft_realloc(seg->text, old_len, old_len + 2);
	if (!new_text)
		return (-1);
	seg->text = new_text;
	seg->text[old_len] = c;
	seg->text[old_len + 1] = '\0';
	return (0);
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

	token = create_empty_token();
	i = *start;
	if (!token)
		return (NULL);
	while (input[i] && input[i] != ' ' && input[i] != '\t')
	{
		if (input[i] == SQ)
		{
			if (process_quoted_segment(input, &i, token, true) == -1)
				return (free_tokens(data), NULL);
		}
		else if (input[i] == DQ)
		{
			if (process_quoted_segment(input, &i, token, false) == -1)
				return (free_tokens(data), NULL);
		}
		else
			if (process_unquoted_chars(input, &i, token) == -1)
				return (free_tokens(data), NULL);
	}
	*start = i;
	return (token);
}
