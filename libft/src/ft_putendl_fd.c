/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:22:22 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 11:05:14 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Outputs the string s to the given file descriptor, followed by a newline.
// Returns the number of characters printed.
// If an error occurs, the function returns -1.
int	ft_putendl_fd(char *s, int fd)
{
	return ((ft_putstr_fd(s, fd)) + (ft_putchar_fd('\n', fd)));
}
