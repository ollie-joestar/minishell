/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:43:16 by hanjkim           #+#    #+#             */
/*   Updated: 2024/04/19 14:01:35 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((unsigned char *)s + i) = c;
		i++;
	}
	return (s);
}

/*#include <stdio.h>

int main()
{
	char buffer [10];

	ft_memset(buffer, 'A', sizeof(buffer));
	printf("Normal buffer filling: %s\n", buffer);
	ft_memset(buffer + 3, 'B', 4);
	printf("Buffer after replacin: %s\n", buffer);
}*/
