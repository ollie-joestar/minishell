/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:49:02 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 10:51:05 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	runcmd(t_data *data)
{
	t_exec *exec;

	exec = data->exec;
	if (exec->type == BUILTIN)
	{
		if (exec->av[0] == 0)
			bruh(data, "cmd is null\n", 1);
		if (ft_strncmp(exec->av[0] , "exit", 4) == 0)
			exit(0);
		if (exec->av[0] == "cd")
		{
			if (exec->av[1] == 0)
				bruh(data, "cd: no arg\n", 1);
			if (chdir(exec->av[1]) < 0)
			{
				ft_putstr_fd("cd: ", 2);
				ft_putstr_fd(exec->av[1], 2);
				bruh(data, ": no such file or directory\n", 1);
			}
		}
	}
	else
		exec_exec(data, exec);
}
