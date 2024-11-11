/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:29:12 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 11:16:12 by oohnivch         ###   ########.fr       */
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

// Allocates (with malloc(3)) and returns a copy of ’s1’ with the characters specified in ’set’ removed from the beginning and the end of the string.
// Returns the trimmed string, or NULL if the allocation fails.
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
/*
#include  <stdio.h>
int main(int argc, char **argv)
{
    if (argc == 3)
    {
        printf("Original string: %s\n", argv[1]);
        printf("Set to trim: %s\n", argv[2]);
        printf("Result of trim: %s\n", ft_strtrim(argv[1], argv[2]));
        return (0);
    }
    else
        return (1);
}*/
