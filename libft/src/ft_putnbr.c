/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:57:07 by oohnivch          #+#    #+#             */
/*   Updated: 2024/07/03 13:03:54 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putnbr(int nb)
{
	int		len;
	int		check;
	long	nbr;

	len = 0;
	if (nb < 0)
		len += ft_putchar('-');
	nbr = (long)nb * (1 - 2 * (nb < 0));
	if (nbr > 9)
		len += ft_putnbr(nbr / 10);
	check = ft_putchar((nbr % 10) + '0');
	if (check == -1)
		return (check);
	return (len + check);
}
