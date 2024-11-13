/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:06:30 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/13 11:11:44 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// The strdup() function allocates sufficient memory for a copy of the string s1, does the copy, and returns a pointer to it.
// If insufficient memory is available, NULL is returned and errno is set to ENOMEM.
char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*ptr;

	i = 0;
	if (!s || !*s)
		return (NULL);
	while (s[i])
		i++;
	ptr = malloc((i + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
