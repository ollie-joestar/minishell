/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:44:50 by hanjkim           #+#    #+#             */
/*   Updated: 2024/04/17 11:18:17 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	input_len(int nb)
{
	int	len;

	len = 0;
	if (nb <= 0)
		len++;
	while (nb)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*str;

	len = input_len(n);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n >= 0)
	{
		while (len > 0)
		{
			str[--len] = (n % 10) + '0';
			n /= 10;
		}
	}
	while (n < 0)
	{
		*str = '-';
		str[--len] = -(n % 10) + '0';
		n /= 10;
	}
	return (str);
}

/*#include <stdio.h>

int main()
{
	printf("%s", ft_itoa(-2147483647));
}*/
