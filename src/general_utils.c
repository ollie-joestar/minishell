/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:18:21 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/12 16:18:59 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bruh(t_data *data, char *s, int status)
{
	if (s)
		ft_putstr_fd(s, 2);
	if (data)
		free(data);
	exit(status);
}
