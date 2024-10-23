/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:45:45 by oohnivch          #+#    #+#             */
/*   Updated: 2024/07/03 15:25:24 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	ft_word_count(const char *str, char sep)
{
	size_t				i;
	size_t				words;
	unsigned char		c;
	const unsigned char	*s;

	if (!ft_strlen(str))
		return (0);
	s = (const unsigned char *)str;
	c = (unsigned char)sep;
	i = 0;
	words = 0;
	while (s[i])
	{
		if ((s[i + 1] == c || !(s[i + 1])) && s[i] != c)
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

static char	**ft_process(char **list, const char *s, char c)
{
	unsigned int	i;
	size_t			j;
	size_t			word;

	i = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			j = 0;
			while (s[i + j] != c && s[i + j])
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

char	**ft_split(char const *s, char c)
{
	char	**list;
	int		words;

	if (!s)
		return (NULL);
	words = ft_word_count(s, c);
	list = (char **)ft_calloc(sizeof(char *), (words + 1));
	if (list == NULL)
		return (NULL);
	list = ft_process(list, s, c);
	if (list == NULL)
		return (NULL);
	return (list);
}
/*#include <stdio.h>
int	main(int argc, char **argv)
{

	if (argc == 3)
	{
		int i = 0;
		char **result = ft_split(argv[1], argv[2][0]);
		if (!result)
			return (1);
		while (result[i])
		{
			printf("%s\n" , result[i]);
			free(result[i]);
			i++;
		}
		free(result);
		return (0);
	}
	else
		return (1);
}*/
