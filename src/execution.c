/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:36:30 by oohnivch          #+#    #+#             */
/*   Updated: 2025/03/06 16:50:52 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command(t_data *data, t_exec *exec)
{
	if (!exec->cmd)
		bruh(data, NULL, data->status);
	(parse_env_into_ev(data), execve(exec->cmd, exec->av, data->ev));
	if (ft_strchr(exec->cmd, '/') || !data->path || !*data->path)
		failed_cmd_full(data, exec);
	else
	{
		if (exec->cmd != NULL)
			mspec2(exec->cmd, "command not found\n");
		bruh(data, NULL, 127);
	}
}

void	builtin(t_data *data, t_exec *exec)
{
	if (exec_len(exec) == 1)
	{
		store_stds(data, exec);
		if (reroute(data, exec))
			return (restore_stds(data, exec));
	}
	if (!(ft_strncmp(exec->cmd, "exit", 5)))
		(restore_stds(data, exec), ft_exit(data, exec));
	else if (!(ft_strncmp(exec->cmd, "echo", 5)))
		echo(data, exec);
	else if (!(ft_strncmp(exec->cmd, "cd", 3)))
		cd(data, exec);
	else if (!(ft_strncmp(exec->cmd, "env", 4)))
		print_env(data);
	else if (!(ft_strncmp(exec->cmd, "pwd", 4)))
		pwd(data, exec);
	else if (!(ft_strncmp(exec->cmd, "export", 7)))
		export(data, exec);
	else if (!(ft_strncmp(exec->cmd, "unset", 6)))
		unset(data, exec);
	if (ft_strncmp(exec->cmd, "exit", 5))
		restore_stds(data, exec);
	if (exec_len(exec) > 1)
		bruh(data, NULL, data->status);
}

void	do_stuff(t_data *data, t_exec *exec)
{
	if (exec->next)
		open_pipe_exec(data, exec);
	fork1(data);
	underscore(data, exec);
	if (0 == lpid(data))
	{
		data->sa_child.sa_handler = SIG_DFL;
		sigemptyset(&data->sa_child.sa_mask);
		data->sa_child.sa_flags = 0;
		sigaction(SIGQUIT, &data->sa_child, NULL);
		reroute(data, exec);
		if (exec->type == CMD)
			command(data, exec);
		else if (exec->av)
			builtin(data, exec);
		bruh(data, "BRUH", data->status);
	}
	if (exec->prev && exec->prev->piped)
		close_pipe_exec(data, exec->prev);
	if (!exec->next && exec->piped)
	{
		mspec("UNREACHABLE CODE execution.c:79\n");
		close_pipe_exec(data, exec);
	}
}

static void	loop_exec(t_data *data, t_exec *exec)
{
	while (exec)
	{
		if (exec_len(data->exec) > 1 || exec->type == CMD)
			do_stuff(data, exec);
		else if (exec->av)
			(underscore(data, exec), builtin(data, exec));
		exec = exec->next;
	}
}

void	run(t_data *data)
{
	t_exec	*exec;
	int		exit_status;
	int		wait_status;

	exit_status = 0;
	exec = data->exec;
	add_history(data->line);
	loop_exec(data, exec);
	if (exec_len(data->exec) > 1 || exec_has_cmd(data->exec))
	{
		wait_status = 1;
		while (wait_status > 0 && wait_status != lpid(data))
			wait_status = wait(&exit_status);
		check_exit_status(data, exit_status);
		if (WIFSIGNALED(exit_status) && WTERMSIG(exit_status) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		while (wait(NULL) > 0)
			;
	}
	(clean_exec(data), ft_free(&data->line));
}
