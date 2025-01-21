/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:52:36 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/21 12:41:02 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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
