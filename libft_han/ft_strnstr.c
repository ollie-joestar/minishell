/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:05:46 by hanjkim           #+#    #+#             */
/*   Updated: 2024/04/10 18:55:31 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = ft_strlen((char *)little);
	if (*little == '\0')
		return ((char *)big);
	if (!len)
		return (NULL);
	while (*big != '\0' && len-- >= i)
	{
		if ((*big == *little) && (ft_memcmp(big, little, i) == 0))
			return ((char *)big);
		big++;
	}
	return (NULL);
}

/*#include <stdio.h>

int main()
{
	const char *big = "Hello World!";
	const char *little = "World";
	size_t len = ft_strlen(big);
	
	char *result = ft_strnstr((void *) 0, little, 0);
	if (result != NULL)
		printf("'%s' in '%s' at index# %ld.\n", little, big, result - big);
	else
		printf("'%s' not found.", little);
}*/
