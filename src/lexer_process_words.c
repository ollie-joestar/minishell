/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_process_words.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:50:16 by hanjkim           #+#    #+#             */
/*   Updated: 2024/12/01 17:06:19 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_char(char **buffer, size_t *current_size, char c)
{
	char	*temp;

	temp = ft_realloc(*buffer, *current_size, *current_size + 2);
	if (!temp)
		return (free(*buffer), -1);
	*buffer = temp;
	(*buffer)[*current_size] = c;
	(*current_size)++;
	return (0);
}

int	process_quote_content(char *input, int *i, t_data *data, char quote)
{
	while (input[*i] != '\0' && input[*i] != quote)
	{
		if (input[*i] == SLASH && data->is_currently_double_quoted
			&& input[*i + 1] != '\0')
		{
			(*i)++;
			if (append_char(&(data->buffer),
					&(data->current_size), input[*i]) == -1)
				return (-1);
			(*i)++;
		}
		else
		{
			if (append_char(&(data->buffer),
					&(data->current_size), input[*i]) == -1)
				return (-1);
			(*i)++;
		}
	}
	return (0);
}

int	process_quote_part(char *input, int *i, t_data *data)
{
	char	quote;

	quote = input[*i];
	data->is_currently_quoted = true;
	data->is_currently_double_quoted = (quote == DQ);
	(*i)++;
	if (process_quote_content(input, i, data, quote) == -1)
		return (-1);
	if (input[*i] == quote)
		return ((*i)++, 0);
	else
		return (-1);
}

int	process_current_c(char *input, int *i, t_data *data)
{
	if (input[*i] == SQ || input[*i] == DQ)
	{
		if (process_quote_part(input, i, data) == -1)
			return (-1);
	}
	else if (input[*i] == SLASH)
	{
		(*i)++;
		if (input[*i] != '\0')
		{
			if (append_char(&(data->buffer),
					&(data->current_size), input[*i]) == -1)
				return (-1);
			(*i)++;
		}
	}
	else
	{
		if (append_char(&(data->buffer),
				&(data->current_size), input[*i]) == -1)
			return (-1);
		(*i)++;
	}
	return (0);
}

char	*parse_word_token(char *input, int *start, int *end, t_data *data)
{
	int	i;

	data->buffer = ft_calloc(1, sizeof(char));
	if (!data->buffer)
		return (NULL);
	data->current_size = 0;
	data->is_currently_quoted = false;
	data->is_currently_double_quoted = false;
	i = *start;
	while (input[i] != '\0' && input[i] != ' ' && input[i] != '\t')
	{
		if (process_current_c(input, &i, data) == -1)
			return (free(data->buffer), NULL);
	}
	if (append_char(&(data->buffer), &(data->current_size), '\0') == -1)
		return (free(data->buffer), NULL);
	*end = i;
	return (data->buffer);
}
