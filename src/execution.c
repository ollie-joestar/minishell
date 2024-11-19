/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:54:00 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/19 15:21:19 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_child_stuff(t_data *data, t_exec *exec)
{
	reroute(exec);
	execve(exec->cmd, exec->av, data->ev);
	if (ft_strchr(exec->av[0], '/'))
	{
		if (0 == access(exec->av[0], F_OK))
		{
			ft_putstr_fd("minishell: permission denied: ", 2);
			bruh(data, exec->av[0], 126);
		}
		ft_putstr_fd("minishell: no such file or directory: ", 2);
		bruh(data, exec->av[0], 127);
	}
	else
	{
		if (0 == access(exec->av[0], F_OK))
		{
			ft_putstr_fd("minishell: permission denied: ", 2);
			bruh(data, exec->av[0], 126);
		}
		ft_putstr_fd("minishell: command not found: ", 2);
		bruh(data, exec->av[0], 127);
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
		do_child_stuff(data, exec);
	if (exec->prev)
		(close(exec->prev->pipe[RD]), close(exec->prev->pipe[WR]));
}

void	give_birth(t_data *data, t_exec *exec)
{
	if (exec->next)
		pipe_exec(data, exec);
	data->pid = fork1(data);
	if (data->pid == -1)
		bruh(data, "Fork failed", 1);
	if (data->pid == 0)
		run_builtin(data, exec);
	if (exec->prev)
		(close(exec->prev->pipe[RD]), close(exec->prev->pipe[WR]));
}

void	run_builtin(t_data *data, t_exec *exec)
{
	int	stdin_copy;
	int	stdout_copy;

	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	if (exec->next || exec->prev)
		return (give_birth(data, exec));
	if (exec->av[0] == 0)
		bruh(data, "cmd is null\n", 1);
	if (!(ft_strncmp(exec->av[0], "exit", 5)))
		bruh(data, "exit", ft_atoi(exec->av[1]));
	else if (!(ft_strncmp(exec->av[0], "echo", 5)))
		echo(data, data->exec);
	else if (!(ft_strncmp(exec->av[0], "cd", 3)))
		cd(data, data->exec);
	else if (!(ft_strncmp(exec->av[0], "env", 4)))
		print_env(data);
	else if (!(ft_strncmp(exec->av[0], "pwd", 4)))
		pwd(data, data->exec);
	else
		bruh(data, "command not found\n", 127);
	reset_stds(stdin_copy, stdout_copy);
}

void	check_exit_status(t_data *data, int exit_status)
{
	if (WIFEXITED(exit_status))
		data->status = WEXITSTATUS(exit_status);
	else if (WIFSIGNALED(exit_status))
		data->status = WTERMSIG(exit_status) + 128;
}

void	runcmd(t_data *data)
{
	t_exec	*exec;
	int		exit_status;
	int		wait_status;

	exec = data->exec;
	while(exec)
	{
		print_exec(exec);
		if (exec->type == CMD)
			do_stuff(data, exec);
		else
			run_builtin(data, exec);
		exec = exec->next;
	}
	add_history(data->line);
	wait_status = 1;
	while (wait_status > 0 && wait_status != data->pid)
		wait_status = wait(&exit_status);
	check_exit_status(data, exit_status);
	while (wait(NULL) > 0)
		;
	clean_exec(data);
	ft_free(&data->line);
}
