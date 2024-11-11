/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:42:19 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 10:54:26 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Checks if the character is a printable character.
// Returns 1 if the character is a printable character, 0 otherwise.
int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
