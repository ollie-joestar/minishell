/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:59:26 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 11:05:34 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Outputs the hexadecimal representation of the unsigned long integer n to the standard output.
// The format is a character that specifies the case of the hexadecimal digits.
// The format can be 'x' or 'X'.
// The function returns the number of characters printed.
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
