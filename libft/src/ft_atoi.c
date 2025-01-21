/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:50:46 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/21 19:10:49 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	num;
	int	sign;
	long long int	test;

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
