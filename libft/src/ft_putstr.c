/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:27:35 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 11:06:21 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Outputs the string s to the standard output.
// Returns the number of characters printed.
// If s is NULL, "(null)" is printed instead.
int	ft_putstr(char *s)
{
	size_t	len;

	if (s == NULL)
		return (ft_putstr("(null)"));
	len = ft_strlen(s);
	return ((int)(write (1, s, len)));
}
