/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:19:32 by oohnivch          #+#    #+#             */
/*   Updated: 2024/12/02 19:11:11 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_data *data, t_exec *exec)
{
	if (exec->av && exec->av[1])
	{
		if (!check_numeric(exec->av[1]))
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(exec->av[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			bruh(data, NULL, 2);
		}
		if (exec->av[2])
			bruh(data, "minishell: exit: too many arguments\n", 1);
		data->status = ft_atoi(exec->av[1]) % 256;
	}
	bruh(data, "exit", data->status);
}
