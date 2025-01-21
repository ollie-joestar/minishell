/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:28:23 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/21 12:40:20 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if ((unsigned const char)s[i] == (unsigned const char)c)
			return ((char *)s + i);
		i++;
	}
	if ((unsigned const char)c == '\0')
		return ((char *)s + i);
	return (0);
}
