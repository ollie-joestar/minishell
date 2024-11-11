/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:42:59 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 10:54:13 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Checks if the character is a digit.
// Returns 1 if the character is a digit, 0 otherwise.
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
