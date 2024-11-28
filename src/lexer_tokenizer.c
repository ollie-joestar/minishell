/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 20:20:47 by hanjkim           #+#    #+#             */
/*   Updated: 2024/11/28 23:51:50 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_spaces(char **line)
{
	while (**line && (**line == ' ' || **line == '\t'))
		(*line)++;
}

char	*parse_regular_token(char **start, char **end)
{
	char *quoted_str;
	size_t len;

	*end = *start;
	len = 0;
	while (**end != '\0' && **end != ' ' && **end != SQ && **end != DQ)
	{
		(*end)++;
		len++;
	}
	quoted_str = ft_substr(*start, 0, len);
	if (!quoted_str)
		return (NULL);
	return (quoted_str);
}

char	*parse_quoted_token(char **start, char **end, bool *single_or_double)
{
	char quote;
	char *quoted_str;
	size_t len;
	char *copy_start;

	quote = **start;
	if (quote == SQ)
		*single_or_double = false;
	else if (quote == DQ)
		*single_or_double = true;
	else
		return (NULL);
	copy_start = *start + 1;
	*end = copy_start;
	while (**end != '\0' && **end != quote)
		(*end)++;
	len = *end - copy_start;
	quoted_str = ft_substr(copy_start, 0, len);
	if (!quoted_str)
		return (NULL);
	(*end)++;
	return (quoted_str);
}
