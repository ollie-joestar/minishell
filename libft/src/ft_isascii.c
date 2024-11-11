/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:41:20 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 10:54:03 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Checks if the character is an ASCII character.
// Returns 1 if the character is an ASCII character, 0 otherwise.
int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
