/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:46:04 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/21 12:40:28 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putptr(unsigned long nb)
{
	int		len;
	int		check;
	char	*base;

	len = 0;
	len += ft_putstr("0x");
	base = "0123456789abcdef";
	if (nb > 15)
		len += ft_puthex((nb / 16), 'x');
	check = ft_putchar(base[nb % 16]);
	if (check == -1)
		return (check);
	return (len + check);
}
