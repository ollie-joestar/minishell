/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:11:54 by oohnivch          #+#    #+#             */
/*   Updated: 2024/08/09 14:18:08 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_calc(int n)
{
	int	i;

	i = 1;
	if (n < 0)
		i = 2;
	while (n > 9 || n < -9)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

static void	ft_putnbr_itoa(int n, char *str)
{
	unsigned int	num;
	int				neg;
	int				i;

	i = 0;
	neg = 0;
	if (n < 0)
		neg = 1;
	if (n == 0)
		str[i++] = '0';
	num = (1 - 2 * neg) * n;
	while (num > 0)
	{
		str[i++] = '0' + (num % 10);
		num /= 10;
	}
	if (neg == 1)
		str[i++] = '-';
	str[i] = '\0';
}

static void	reverse(char *str)
{
	char	temp;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str);
	while (i < len / 2)
	{
		temp = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = temp;
		i++;
	}
}

char	*ft_itoa(int n)
{
	int		size;
	char	*ptr;

	size = ft_calc(n);
	size++;
	ptr = ft_calloc(size, sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_putnbr_itoa(n, ptr);
	reverse(ptr);
	return (ptr);
}
/*
int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		int	num;

		num = ft_atoi(argv[1]);
		printf("The number given: %d\n", num);
		printf("Space needed for it: %d\n", ft_calc(num));
		printf("String result: %s\n", ft_itoa(num));
//		printf("Real result: %s\n", itoa(num));
		return (0);
	}
	else
		return (1);
}*/
