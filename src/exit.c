/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:19:32 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/14 15:23:35 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	numeric_check(t_data *data, char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return ;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			if (exec_len(data->exec) == 1)
				ft_putstr_fd("exit\n", STDERR_FILENO);
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			bruh(data, NULL, 2);
		}
		i++;
	}
}

void	ft_exit(t_data *data, t_exec *exec)
{
	if (exec->av && exec->av[1])
	{
		numeric_check(data, exec->av[1]);
		if (exec->av[2])
		{
			data->status = 1;
			if (exec_len(exec) < 2)
			{
				ft_putstr_fd("exit\n", STDERR_FILENO);
				ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
				return ;
			}
			else
				bruh(data, "minishell: exit: too many arguments", STDERR_FILENO);
		}
		data->status = ft_atoi(exec->av[1]) % 256;
		/*if (data->status < 0 || data->status > 255)*/
		/*	data->status = 69;*/
	}
	if (exec_len(exec) == 1)
		bruh(data, "exit", data->status);
	bruh(data, NULL, data->status);
}
