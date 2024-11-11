/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:17:24 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 11:05:02 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Outputs the character c to the given file descriptor.
// Returns the number of characters printed.
// If an error occurs, the function returns -1.
int	ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}
