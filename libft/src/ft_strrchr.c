/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:09:15 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 11:15:35 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// The strrchr() function locates the last occurrence of c (converted to a char) in the string pointed to by s.
// The terminating null character is considered to be part of the string.
// Returns a pointer to the located character, or NULL if the character does not appear in the string.
char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (const char)c)
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
}
