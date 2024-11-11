/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:00:55 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 11:23:02 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_nlcheck(char const *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (s[i] == '\n');
}


// Returns the length of the line until newline in the buffer including the newline character (if present).
// If the buffer is NULL, the function returns 0.
// If the buffer does not contain a newline character, the function returns the length of the buffer.
size_t	ft_linelen(char *buffer)
{
	size_t	i;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	return (i + (buffer[i] == '\n'));
}

void	ft_free(char **ptr)
{
	if (!ptr || !*ptr)
		return ;
	free(*ptr);
	*ptr = NULL;
}
