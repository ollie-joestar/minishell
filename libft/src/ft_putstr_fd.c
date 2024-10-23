/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:19:09 by oohnivch          #+#    #+#             */
/*   Updated: 2024/09/11 19:43:11 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (s == NULL)
		return (ft_putstr("(null)"));
	len = ft_strlen(s);
	return ((int)(write (fd, s, len)));
}
