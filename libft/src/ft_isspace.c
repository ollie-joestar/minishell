/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:31:00 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 10:54:34 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Checks if the character is a whitespace character.
// Returns 1 if the character is a whitespace character, 0 otherwise.
int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
