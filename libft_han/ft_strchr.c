/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:59:02 by hanjkim           #+#    #+#             */
/*   Updated: 2024/09/13 20:31:08 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

/*#include <stdio.h>

int main ()
{
	char buffer[] = "Hello World!";
	char *result;

	result = ft_strchr(buffer, 'p');
	 if (result != NULL) {
        printf("Char first found at index#: %ld\n", result - buffer);
       // printf("Char first found at index#: %c\n", *result);
    } else {
        printf("Char not available\n");
    }
}*/
