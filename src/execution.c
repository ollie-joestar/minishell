/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:54:00 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 15:23:25 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_child_stuff(t_data *data)
{
	reroute(data);
	find_access(data);
	execve(data->exec->av[0], data->exec->av, data->ev);
	if (ft_strchr(data->exec->av[0], '/'))
	{
		if (0 == access(data->exec->av[0], F_OK))
		{
			write(2, "pipex: permission denied: ", 26);
			bruh(data, data->exec->av[0], 126);
		}
		write(2, "pipex: no such file or directory: ", 34);
		bruh(data, data->exec->av[0], 127);
	}
	else
	{
		if (0 == access(data->exec->av[0], F_OK))
		{
			write(2, "pipex: permission denied: ", 26);
			bruh(data, data->exec->av[0], 126);
		}
		write(2, "pipex: command not found: ", 26);
		bruh(data, data->exec->av[0], 127);
	}
}

void	run_exec(t_data *data)
{
	int	p[2];
	t_exec	*exec;
	pid_t pid;

	exec = data->exec;
	while(exec)
	{
		if (exec->next)
		{
			if (pipe(p) == -1)
				bruh(data, "Pipe failed", 1);
		}
		pid = fork1(data);
		if (pid == -1)
			bruh(data, "Fork failed", 1);
		if (pid == 0)
		{
			do_child_stuff(data);
		}
		else
		{
			if (exec->next)
				close(p[WR]);
			if (exec->prev)
				close(p[RD]);
			waitpid(pid, &data->status, 0);
		}
		exec = exec->next;
	}
}
