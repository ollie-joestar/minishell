/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:10:40 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 11:17:07 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	s_check(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;

	s_len = ft_strlen(s);
	if (start < s_len)
	{
		if (start + len > s_len)
			return (s_len - start);
		else
			return (len);
	}
	return (0);
}

// Allocates (with malloc(3)) and returns a substring from the string ’s’.
// The substring begins at index ’start’ and is of maximum size ’len’.
// Returns the substring, or NULL if the allocation fails.
// If ’start’ is out of range, the behavior is undefined.
// If ’len’ is greater than the length of the substring, the behavior is undefined.
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	mem;
	char	*ptr;

	if (!s)
		return (NULL);
	mem = s_check(s, start, len);
	ptr = malloc ((mem + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	if (!mem)
	{
		ptr[i] = 0;
		return (ptr);
	}
	while (s[i + start] && i < mem)
	{
		ptr[i] = (unsigned char)s[i + start];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
/*
#include <stdio.h>
int	main(void)
{
//	if (argc == 2)
//	{
//		printf("%s\n",argv[1]);
		printf("%s\n",ft_substr("hola", 4294967295, 0));
		return (0);
//	}
}*/
