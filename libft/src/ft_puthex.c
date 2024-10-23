/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:59:26 by oohnivch          #+#    #+#             */
/*   Updated: 2024/07/03 13:03:53 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_puthex(unsigned long n, const char format)
{
	int		len;
	int		check;
	char	*base;

	base = "0123456789ABCDEF";
	if (format == 'x')
		base = "0123456789abcdef";
	len = 0;
	if (n > 15)
		len += ft_puthex((n / 16), format);
	check = ft_putchar(base[n % 16]);
	if (check == -1)
		return (check);
	return (len + check);
}
