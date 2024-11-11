/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:13:52 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 11:04:33 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Outputs the character c to the standard output.
// Returns the number of characters printed.
int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}
