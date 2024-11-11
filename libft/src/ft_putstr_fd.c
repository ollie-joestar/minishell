/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:19:09 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 11:06:51 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Outputs the string s to the given file descriptor.
// Returns the number of characters printed.
// If s is NULL, "(null)" is printed instead.
int	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (s == NULL)
		return (ft_putstr("(null)"));
	len = ft_strlen(s);
	return ((int)(write (fd, s, len)));
}
