/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:57:00 by hanjkim           #+#    #+#             */
/*   Updated: 2024/04/08 18:46:40 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	size_t	sign;
	size_t	value;

	sign = 1;
	value = 0;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n'
		||*nptr == '\v' || *nptr == '\f' || *nptr == '\r')
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (ft_isdigit(*nptr))
	{
		value = value * 10 + (*nptr - '0');
		nptr++;
	}
	return (sign * value);
}

/*#include <stdio.h>

int main(int argc, char *argv[])
{
	int i;

	i = 1;	
	if (argc < 2)
	{
		printf("%s\n", argv[0]);
		return (1);
	}
	while (i < argc)
	{
		printf("%d\n", ft_atoi(argv[i]));
		i++;
	}
	return (0);
}*/
