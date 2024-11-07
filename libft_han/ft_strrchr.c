/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:07:52 by hanjkim           #+#    #+#             */
/*   Updated: 2024/04/12 16:57:52 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen((char *)s) + 1;
	while (i--)
	{
		if (*(s + i) == (char)c)
			return ((char *)(s + i));
	}
	return (0);
}

/*#include <stdio.h>

int main ()
{
	char buffer[] = "Hello World!";
	char *result;

	result = ft_strrchr(buffer, '\0');
	printf("%s\n", result);
	if (result != NULL) 
	{
		printf("Char last found at index#: %ld\n", result - buffer);
		// printf("Char first found at index#: %c\n", *result);
	}
	else 
	{
		printf("Char not available\n");
	}
}*/
