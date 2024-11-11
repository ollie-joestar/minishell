/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:50:46 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 10:55:17 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Converts the initial portion of the string pointed to by str to int representation.
// The expected string format is an optional plus or minus sign, followed by a sequence of digits.
// The function stops reading the string at the first character that cannot be converted to a number.
// The function returns the converted number.
// If the string is empty or does not contain any digits, the function returns 0.
int	ft_atoi(const char *str)
{
	int	i;
	int	num;
	int	sign;

	sign = 1;
	num = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		sign = sign - (2 * (str[i++] == '-'));
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + sign * (str[i++] - '0');
	return (num);
}
