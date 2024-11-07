/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:47:51 by hanjkim           #+#    #+#             */
/*   Updated: 2024/04/19 14:02:55 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	length;

	i = 0;
	length = 0;
	while (src[length])
		length++;
	while (src[i] && i + 1 < size)
	{
		dest[i] = src[i];
		i++;
	}
	if (size)
		dest[i] = '\0';
	return (length);
}

/*#include <stdio.h>

int main()
{
	char dest[20];
	const char *src = "Hello World!";

	printf("%s\n", src);

	size_t size = ft_strlen(dest);
	size_t result = ft_strlcpy(dest, src, size);
	printf("%s\n", dest);
	printf("%zu", result);
}*/
