/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:31:08 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/18 15:38:29 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_data *data, t_exec *exec)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (exec->av[1] && *exec->av[1] && !ft_strncmp(exec->av[1], "-n", 3))
		n = 1;
	i += n;
	while (exec->av[++i])
	{
		ft_putstr(exec->av[i]);
		if (exec->av[i + 1])
			ft_putchar(' ');
	}
	if (!n)
		ft_putchar('\n');
	data->status = 0;
}
