/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:36:51 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 11:05:55 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Outputs the integer n to the given file descriptor.
// Returns the number of characters printed.
int	ft_putnbr_fd(int n, int fd)
{
	int		len;
	int		check;
	long	nbr;

	len = 0;
	if (n < 0)
		len += ft_putchar_fd('-', fd);
	nbr = (long)n * (1 - 2 * (n < 0));
	if (nbr > 9)
		len += ft_putnbr_fd(nbr / 10, fd);
	check = ft_putchar_fd((nbr % 10) + '0', fd);
	if (check == -1)
		return (check);
	return (len + check);
}
