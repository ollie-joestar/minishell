/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:17:15 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 11:03:37 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_format(va_list args, const char format)
{
	void	*ptr;

	if (format == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (format == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (format == 'd' || format == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (format == 'u')
		return (ft_putuint(va_arg(args, unsigned int)));
	else if (format == 'x' || format == 'X')
		return (ft_puthex(va_arg(args, unsigned int), format));
	else if (format == '%')
		return (ft_putchar(format));
	else if (format == 'p')
	{
		ptr = va_arg(args, void *);
		if (!ptr)
			return (ft_putstr("(nil)"));
		return (ft_putptr((unsigned long)ptr));
	}
	else
		return (-1);
}

// Outputs a formatted string to the standard output.
// Returns the number of characters printed.
// Returns -1 if the format is invalid.
// The format is a string that can contain plain text and format specifiers.
// A format specifier is a % character followed by a conversion specifier.
// The conversion specifier is a character that specifies the type of conversion to be applied.
// The conversion specifiers are:
// c - character
// s - string
// p - pointer
// d - integer
// i - integer
// u - unsigned integer
// x - hexadecimal integer
// X - hexadecimal integer
// % - percentage
// The function can take any number of arguments.
// The arguments must match the conversion specifiers in the format string.
int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		len;
	int		i;

	len = 0;
	i = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] && ft_strchr("cspdiuxX%", str[i + 1]))
		{
			len += ft_format(args, str[i + 1]);
			i++;
		}
		else if (str[i] == '%' && \
			(!ft_strchr("cspdiuxX%", str[i + 1]) || str[i + 1] == '\0'))
			return (-1);
		else
			len += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (len);
}
