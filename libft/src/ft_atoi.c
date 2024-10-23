/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:50:46 by oohnivch          #+#    #+#             */
/*   Updated: 2024/07/03 13:09:56 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	isspace(int c)
{
	return ((c >= 9 && c <= 13) || (c == 32));
}

int	ft_atoi(const char *str)
{
	int	i;
	int	num;
	int	sign;

	sign = 1;
	num = 0;
	i = 0;
	while (isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		sign = sign - (2 * (str[i++] == '-'));
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + sign * (str[i++] - '0');
	return (num);
}
/*
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        (void) argc;
        printf("ft_atoi result : %d\n", ft_atoi(argv[1]));
        printf("atoi result : %d\n", atoi(argv[1]));
        return (0);
    }
    else
        return (1);
}*/
