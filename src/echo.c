/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:31:08 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/14 11:00:12 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_n_flag(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '-')
		i++;
	else
		return (0);
	while (str[i] == 'n')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

void	echo(t_data *data, t_exec *exec)
{
	int	i;
	int	n;

	i = 0;
	n = check_n_flag(exec->av[1]);
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
