/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printerr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:15:27 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/21 12:36:51 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_format(va_list args, const char format)
{
	if (format == 'c')
		return (ft_putchar_fd(va_arg(args, int), 2));
	else if (format == 's')
		return (ft_putstr_fd(va_arg(args, char *), 2));
	else if (format == 'd' || format == 'i')
		return (ft_putnbr_fd(va_arg(args, int), 2));
	else
		return (-1);
}

// Outputs a formatted string to the standard output.
// Returns the number of characters printed.
// Returns -1 if the format is invalid.
// The format is a string that can contain plain text and format specifiers.
// A format specifier is a % character followed by a conversion specifier.
// The conversion specifiers are:
// c - character
// s - string
// d - integer
// i - integer
// The function can take any number of arguments.
// The arguments must match the conversion specifiers in the format string.
int	ft_printerr(const char *str, ...)
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
			(!ft_strchr("sdi%", str[i + 1]) || str[i + 1] == '\0'))
			return (-1);
		else
			len += ft_putchar_fd(str[i], 2);
		i++;
	}
	va_end(args);
	return (len);
}
