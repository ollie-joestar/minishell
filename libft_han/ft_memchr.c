/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:38:26 by hanjkim           #+#    #+#             */
/*   Updated: 2024/04/08 18:49:24 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*((unsigned char *)s + i) == (unsigned char)c)
			return ((unsigned char *)s + i);
		i++;
	}
	return (NULL);
}

/*#include <stdio.h>

int main()
{
	char buffer[] = "Hello World!";
	char *result;

	result = ft_memchr(buffer, 'l', sizeof(buffer));
	if (result != NULL) {
        printf("Char first found at index#: %ld\n", result - buffer);
    } else {
        printf("Char not available\n");
    }
}*/
