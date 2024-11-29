/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_process_words.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:50:16 by hanjkim           #+#    #+#             */
/*   Updated: 2024/11/30 00:13:25 by hanjkim          ###   ########.fr       */
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

int	process_quote_part(char *input, int *i, char **buffer, size_t *current_size)
{
	char	quote;

	quote = input[*i];
	(*i)++;
	while (input[*i] != '\0' && input[*i] != quote)
	{
		if (input[*i] == '\\' && quote == DQ && input[*i + 1] != '\0')
		{
			(*i)++;
			if (append_char(buffer, current_size, input[*i]) == -1)
				return (-1);
			(*i)++;
		}
		else
		{
			if (append_char(buffer, current_size, input[*i]) == -1)
				return (-1);
			(*i)++;
		}
	}
	if (input[*i] == quote)
		return ((*i)++, 0);
	else
		return (-1);
}

int	process_current_c(char *input, int *i, char **buffer, size_t *current_size)
{
	if (input[*i] == SQ || input[*i] == DQ)
	{
		if (process_quote_part(input, i, buffer, current_size) == -1)
			return (-1);
	}
	else if (input[*i] == '\\')
	{
		(*i)++;
		if (input[*i] != '\0')
		{
			if (append_char(buffer, current_size, input[*i]) == -1)
				return (-1);
			(*i)++;
		}
	}
	else
	{
		if (append_char(buffer, current_size, input[*i]) == -1)
			return (-1);
		(*i)++;
	}
	return (0);
}

char	*parse_word_token(char *input, int *start, int *end)
{
	char	*buffer;
	size_t	current_size;
	int		i;

	buffer = ft_calloc(1, sizeof(char));
	if (!buffer)
		return (NULL);
	current_size = 0;
	i = *start;
	while (input[i] != '\0' && input[i] != ' ' && input[i] != '\t')
	{
		if (process_current_c(input, &i, &buffer, &current_size) == -1)
			return (NULL);
	}
	if (append_char(&buffer, &current_size, '\0') == -1)
		return (NULL);
	*end = i;
	return (buffer);
}
