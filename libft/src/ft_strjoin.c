/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:22:13 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/13 11:46:23 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Allocates (with malloc(3)) and returns a new string, which is the result of the concatenation of ’s1’ and ’s2’.
// Returns NULL if the allocation fails.
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	size_t	i;
	size_t	j;
	char	*ptr;

	if (!s1 || !s2 || !*s1 || !*s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	ptr = ft_calloc(size + 1, sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		ptr[i + j] = s2[j];
		j++;
	}
	return (ptr);
}
