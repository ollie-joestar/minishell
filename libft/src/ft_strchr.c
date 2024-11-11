/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:28:23 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 11:08:00 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// The strchr() function locates the first occurrence of c (converted to a char) in the string pointed to by s.
// The terminating null character is considered to be part of the string; therefore if c is `\0`,
// the functions locate the terminating `\0`.
// The functions strchr() return a pointer to the located character, or NULL if the character does not appear in the string.
char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if ((unsigned const char)s[i] == (unsigned const char)c)
			return ((char *)s + i);
		i++;
	}
	if ((unsigned const char)c == '\0')
		return ((char *)s + i);
	return (0);
}
