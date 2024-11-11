/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:20:05 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 11:12:07 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// The strlcat() function appends the NUL-terminated string src to the end of dest.
// It will append at most size - strlen(dest) - 1 bytes, NUL-terminating the result.
// The strlcat() function returns the total length of the string it tried to create.
// For strlcat() that means the initial length of dest plus the length of src.
// It is the caller's responsibility to handle this.
size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	offset;
	size_t	index;
	size_t	len;

	offset = ft_strlen(dest);
	len = ft_strlen(src);
	if (size == 0 || size <= offset)
		return (len + size);
	index = 0;
	while (index < len && index + offset < size - 1)
	{
		dest[offset + index] = src[index];
		index++;
	}
	dest[offset + index] = 0;
	return (len + offset);
}
