/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:27:52 by hanjkim           #+#    #+#             */
/*   Updated: 2024/04/12 15:42:34 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	di;
	size_t	si;
	size_t	length;

	if (size == 0)
		return (ft_strlen(src));
	else if (size < ((size_t)ft_strlen(dest)))
		length = ft_strlen(src) + size;
	else
		length = ft_strlen(src) + ft_strlen(dest);
	di = 0;
	while (dest[di] != '\0')
		di++;
	si = 0;
	while (src[si] != '\0' && di + 1 < size)
	{
		dest[di] = src[si];
		si++;
		di++;
	}
	dest[di] = '\0';
	return (length);
}

/*#include <stdio.h>

int main()
{
	char dest[20] = "Hello";
	const char *src = "World!";
	size_t size = ft_strlen(dest);

	printf("%s\n", dest);

	size_t length = ft_strlcat(dest, src, size);

	printf("%s\n", dest);
	printf("%zu\n", length);
}*/
