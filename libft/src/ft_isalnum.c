/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:44:55 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 10:53:38 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Checks if the character is an alphanumeric character.
// Returns 1 if the character is an alphanumeric character, 0 otherwise.
int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
