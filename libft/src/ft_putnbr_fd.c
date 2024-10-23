/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:36:51 by oohnivch          #+#    #+#             */
/*   Updated: 2024/09/11 19:45:58 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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
