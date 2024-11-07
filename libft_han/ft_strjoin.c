/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:23:20 by hanjkim           #+#    #+#             */
/*   Updated: 2024/04/08 18:48:14 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	i_new;
	char	*str_new;
	size_t	size;

	i_new = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	size = (ft_strlen(s1) + ft_strlen(s2) + 1);
	str_new = malloc(sizeof(char) * size);
	if (!str_new)
		return (NULL);
	while (s1[i])
		str_new[i_new++] = s1[i++];
	i = 0;
	while (s2[i])
		str_new[i_new++] = s2[i++];
	str_new[i_new] = '\0';
	return (str_new);
}
