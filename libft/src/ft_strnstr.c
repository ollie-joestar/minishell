/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:44:44 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/21 12:39:29 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	n_len;

	j = 0;
	n_len = ft_strlen(little);
	if (!(little[j]))
		return ((char *)big);
	if (!len)
		return (0);
	i = 0;
	while (big[i] && i <= len - n_len)
	{
		while ((unsigned char)big[i + j] == (unsigned char)little[j])
		{
			if (!(little[j + 1]) && j < len)
				return ((char *)big + i);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
