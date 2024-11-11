/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:02:44 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 11:01:16 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Copies n bytes from memory area src to memory area dest.
// The memory areas may overlap.
// Returns the original value of dest.
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d == 0 && s == 0 && n)
		return (0);
	if (d == s || n == 0)
		return (dest);
	i = 0;
	while (i < n)
	{
		if (s < d && s + n > d)
			d[n - 1 - i] = s[n - 1 - i];
		else
			d[i] = s[i];
		i++;
	}
	return (dest);
}
