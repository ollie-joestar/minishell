/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:51:58 by oohnivch          #+#    #+#             */
/*   Updated: 2025/02/11 17:12:51 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	ft_word_count(const char *str, char *sep)
{
	size_t				i;
	size_t				words;
	const char			*c;
	const unsigned char	*s;

	if (!ft_strlen(str))
		return (0);
	s = (const unsigned char *)str;
	c = (const char *)sep;
	i = 0;
	words = 0;
	while (s[i])
	{
		if ((ft_strchr(c, s[i + 1]) || !(s[i + 1])) && !ft_strchr(c, s[i]))
			words++;
		i++;
	}
	return (words);
}

static void	*mem_free(char **list, size_t word)
{
	size_t	i;

	i = 0;
	while (i < word)
	{
		free(list[i]);
		i++;
	}
	free(list);
	return (NULL);
}

static char	**ft_process(char **list, const char *s, char *c)
{
	unsigned int	i;
	size_t			j;
	size_t			word;

	i = 0;
	word = 0;
	while (s[i])
	{
		if (ft_strchr(c, s[i]))
			i++;
		else
		{
			j = 0;
			while (!ft_strchr(c, s[i + j]) && s[i + j])
				j++;
			list[word] = ft_substr(s, i, j);
			if (list[word] == NULL)
				return (mem_free(list, word));
			i += j;
			word++;
		}
	}
	return (list);
}

// Splits the string s using the character c as a delimiter.
// Returns an array of strings obtained by splitting s using c as a delimiter.
// The array is terminated by a NULL pointer.
// If the allocation fails, the function returns NULL.
//
char	**ft_split_set(char const *s, char *set)
{
	char	**list;
	int		words;

	if (!s)
		return (NULL);
	words = ft_word_count(s, set);
	list = (char **)ft_calloc(sizeof(char *), (words + 1));
	if (list == NULL)
		return (NULL);
	list = ft_process(list, s, set);
	if (list == NULL)
		return (NULL);
	return (list);
}
