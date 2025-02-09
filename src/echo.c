/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:31:08 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/27 15:20:33 by oohnivch         ###   ########.fr       */
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
	if (str[i] == '\0' && i > 1)
		return (1);
	return (0);
}

void	echo(t_data *data, t_exec *exec)
{
	int	i;
	int	n;
	int	check;

	i = 1;
	n = 0;
	while (1)
	{
		check = check_n_flag(exec->av[i]);
		if (check)
			n = i++;
		else
			break ;
	}
	while (exec->av[i])
	{
		ft_putstr(exec->av[i]);
		if (exec->av[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (!n)
		ft_putchar('\n');
	data->status = 0;
}
