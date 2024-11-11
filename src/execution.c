/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:54:00 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 16:45:56 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_child_stuff(t_data *data)
{
	reroute(data);
	execve(data->exec->cmd, data->exec->av, data->ev);
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

void	do_stuff(t_data *data, t_exec *exec)
{
	if (exec->next)
	{
		if (pipe(exec->pipe) == -1)
			bruh(data, "Pipe failed", 1);
	}
	data->pid = fork1(data);
	if (data->pid == -1)
		bruh(data, "Fork failed", 1);
	if (data->pid == 0)
		do_child_stuff(data);
	if (exec->prev)
		(close(exec->prev->pipe[RD]), close(exec->prev->pipe[WR]));
	if (exec->next)
		do_stuff(data, exec->next);
	else
		(close(exec->pipe[WR]), close(exec->pipe[RD]));
}

void	run_exec(t_data *data)
{
	t_exec	*exec;
	int		exit_status;
	int		wait_status;

	exit_status = 0;
	exec = data->exec;
	while(exec)
		do_stuff(data, exec);
	wait_status = 1;
	while (wait_status > 0 && wait_status != data->pid)
		wait_status = wait(&exit_status);
	if (WIFEXITED(exit_status))
		data->status = WEXITSTATUS(exit_status);
	else if (WIFSIGNALED(exit_status))
		data->status = WTERMSIG(exit_status) + 128;
	while (wait(NULL) > 0)
		;
	clean_exec(data);
	return ;
}
