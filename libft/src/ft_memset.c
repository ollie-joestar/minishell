/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:52:36 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 11:02:38 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Fills the first n bytes of the memory area pointed to by s with the constant byte c.
// Returns the original value of s.
void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*mem;
	unsigned char	value;

	mem = s;
	i = 0;
	value = (unsigned char)c;
	while (i < n)
	{
		mem[i] = value;
		i++;
	}
	return (s);
}
