/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:36:46 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 11:00:10 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Locates the first occurrence of c (converted to an unsigned char) in string s.
// Returns a pointer to the byte located, or NULL if no such byte exists within n bytes.
// The terminating null byte is considered to be part of the string.
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*src;
	unsigned char		chr;

	i = 0;
	src = (const unsigned char *)s;
	chr = (unsigned char)c;
	while (i < n)
	{
		if (src[i] == chr)
			return ((void *)(src + i));
		i++;
	}
	return (NULL);
}
