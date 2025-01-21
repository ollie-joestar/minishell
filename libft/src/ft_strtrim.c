/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:29:12 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/21 12:39:06 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	check(char c, char const *set)
{
	size_t	i;

	i = 0;
	while ((unsigned char const)set[i])
	{
		if ((unsigned char const)set[i] == (unsigned char const)c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	size_calc(char const *s1, char const *set, size_t *sptr)
{
	size_t	size;
	size_t	end;
	size_t	start;

	start = *sptr;
	end = ft_strlen(s1);
	while (start <= end && check(s1[start], set))
		start++;
	while (end > start && check(s1[end - 1], set))
		end--;
	if (start >= end)
		return (0);
	size = end - start;
	*sptr = start;
	return (size);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	*sptr;
	size_t	size;
	char	*ptr;

	start = 0;
	sptr = &start;
	size = size_calc(s1, set, sptr);
	ptr = ft_substr(s1, *sptr, size);
	return (ptr);
}
