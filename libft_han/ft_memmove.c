/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:11:38 by hanjkim           #+#    #+#             */
/*   Updated: 2024/04/19 14:01:23 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == src || n == 0)
		return (dest);
	while (i < n)
	{
		if (dest < src)
			*((unsigned char *)dest + i) = *((unsigned char *)src + i);
		else
			*((unsigned char *)dest + n - 1 - i)
				= *((unsigned char *)src + n - 1 - i);
		i++;
	}
	return (dest);
}

/*#include <stdio.h>

int main()
{
	char src[] = "Hello World!";
	char dest [20];
	
	ft_memmove(dest, src, sizeof(src));
	printf("This is src: %s\n", src);
	printf ("This is dest: %s\n", dest);
}*/
