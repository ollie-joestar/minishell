/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:50:46 by oohnivch          #+#    #+#             */
/*   Updated: 2025/03/03 20:03:51 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	num;
	int		sign;

	sign = 1;
	num = 0;
	i = 0;
	if (!str)
		return (0);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		sign = sign - (2 * (str[i++] == '-'));
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + sign * (str[i++] - '0');
	if (num > 2147483647 || num < -2147483648)
		return (-1);
	return ((int)num);
}
