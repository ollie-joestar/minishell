/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:39:47 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 11:00:38 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Compares byte string s1 against byte string s2.
// Both strings are assumed to be n bytes long.
// Returns zero if the two strings are identical, otherwise returns the difference between the first two differing bytes.
// Zero-length strings are always identical.
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*str1;
	const unsigned char	*str2;

	i = 0;
	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	if (n == 0)
		return (0);
	while (str1[i] == str2[i] && i < n - 1)
		i++;
	return (str1[i] - str2[i]);
}
