/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:54:00 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/13 14:16:39 by oohnivch         ###   ########.fr       */
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
			ft_putstr_fd("minishell: permission denied: ", 2);
			bruh(data, data->exec->av[0], 126);
		}
		ft_putstr_fd("minishell: no such file or directory: ", 2);
		bruh(data, data->exec->av[0], 127);
	}
	else
	{
		if (0 == access(data->exec->av[0], F_OK))
		{
			ft_putstr_fd("minishell: permission denied: ", 2);
			bruh(data, data->exec->av[0], 126);
		}
		ft_putstr_fd("minishell: command not found: ", 2);
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
	if (!exec->next)
		(close(exec->pipe[WR]), close(exec->pipe[RD]));
}


void	run_builtin(t_data *data)
{
	int	stdin_copy;
	int	stdout_copy;

	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	if (data->exec->av[0] == 0)
		bruh(data, "cmd is null\n", 1);
	if (!(ft_strncmp(data->exec->av[0], "exit", 5)))
		bruh(data, NULL, data->status);
	else if (!(ft_strncmp(data->exec->av[0], "echo", 5)))
		echo(data, data->exec);
	reset_stds(stdin_copy, stdout_copy);
}

void	runcmd(t_data *data)
{
	t_exec	*exec;
	int		exit_status;
	int		wait_status;

	exit_status = 0;
	exec = data->exec;
	while(exec)
	{
		if (exec->type == CMD)
			do_stuff(data, exec);
		else
			run_builtin(data);
		exec = exec->next;
	}
	add_history(data->line);
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
