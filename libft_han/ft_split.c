/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:04:58 by hanjkim           #+#    #+#             */
/*   Updated: 2024/04/17 14:44:30 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	words;
	size_t	i;

	words = 0;
	i = 0;
	while (*(s + i))
	{
		if (*(s + i) != c)
		{
			words++;
			while (*(s + i) && *(s + i) != c)
				i++;
		}
		else if (*(s + i) == c)
			i++;
	}
	return (words);
}

static size_t	word_len(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*(s + i) && *(s + i) != c)
		i++;
	return (i);
}

static void	free_array(size_t i, char **arr)
{
	while (i > 0)
	{
		i--;
		free(*(arr + i));
	}
	free(arr);
}

static char	**split(char const *s, char c, char **arr, size_t words_count)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < words_count)
	{
		while (*(s + j) && *(s + j) == c)
			j++;
		*(arr + i) = ft_substr(s, j, word_len((s + j), c));
		if (!*(arr + i))
		{
			free_array(i, arr);
			return (NULL);
		}
		while (*(s + j) && *(s + j) != c)
			j++;
		i++;
	}
	*(arr + i) = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	arr = (char **)malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (NULL);
	arr = split(s, c, arr, words);
	return (arr);
}

/*#include <stdio.h>

int main() {
	char *str = "Hello/World/this/is/a/test";
	char **result = ft_split(str, '/');
	
	printf("Original string: %s\n", str);
	printf("Split string:\n");
	if (!result)
		return (0);
	int i = 0;
	while (result[i] != NULL) {
		printf("%s\n", result[i]);
		i++;
	}
	
	return (0);
}*/
