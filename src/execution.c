/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:35:58 by oohnivch          #+#    #+#             */
/*   Updated: 2025/02/11 18:41:04 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	failed_cmd_full(t_data *data, t_exec *exec)
{
	struct stat file_stat;

	if (0 == access(*exec->av, F_OK))
	{
		if (stat(*exec->av, &file_stat) == 0)
		{
			if (S_ISDIR(file_stat.st_mode))
				mspec2(exec->cmd, "Is a directory\n");
			else
				mspec2(exec->cmd, "Permission denied\n");
		}
		bruh(data, NULL, 126);
	}
	else
		mspec2(exec->cmd, "No such file or directory\n");
	bruh(data, NULL, 127);
}

void	command(t_data *data, t_exec *exec)
{
	if (!exec->cmd)
		bruh(data, NULL, 0);
	(parse_env_into_ev(data), execve(exec->cmd, exec->av, data->ev));
	if (exec->av && ft_strchr(*exec->av, '/'))
		failed_cmd_full(data, exec);
	else if (exec->av)
	{
		if (0 == access(exec->cmd, F_OK) && ft_strncmp(exec->cmd, ".", 2) &&
		ft_strncmp(exec->cmd, "..", 3))
			(mspe(exec->cmd), bruh(data, NULL, 126));
		if (exec->cmd != NULL && *exec->cmd)
			mspec2(exec->cmd, "command not found\n");
		bruh(data, NULL, 127);
	}
}

static void	reset_stdout(int stdout_copy)
{
	if (stdout_copy == -1 || stdout_copy == STDOUT_FILENO)
		return ;
	/*safe_close(STDOUT_FILENO);*/
	dup2(stdout_copy, STDOUT_FILENO);
	safe_close(stdout_copy);
}

void	builtin(t_data *data, t_exec *exec)
{
	int32_t	stdout_copy;

	stdout_copy = -1;
	if (exec_len(exec) == 1)
		(stdout_copy = dup(STDOUT_FILENO), reroute(data, exec));
	if (!(ft_strncmp(exec->cmd, "exit", 5)))
		(reset_stdout(stdout_copy), ft_exit(data, exec));
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
	else
		bruh(data, "it's not a builtin, my bad (^_^)\n", 127);
	if (exec_len(exec) > 1)
		(close_pipe_exec(data, exec), bruh(data, NULL, 0));
	else if (ft_strncmp(exec->cmd, "exit", 5))
		reset_stdout(stdout_copy);
}

void	do_stuff(t_data *data, t_exec *exec)
{
	/*ft_printf("DOING STUFF\n");*/
	if (exec->next)
		open_pipe_exec(data, exec);
	/*signal(SIGINT, SIG_IGN);*/
	fork1(data);
	underscore(data, exec);
	if (!lpid(data))
	{
		/*signal(SIGINT, SIG_DFL);*/
		reroute(data, exec);
		if (exec->type == CMD)
			command(data, exec);
		else if (exec->av)
			builtin(data, exec);
		bruh(data, NULL, data->status);
	}
	close_pipe_exec(data, exec->prev);
	if (!exec->next)
		close_pipe_exec(data, exec);
	/*waitpid(data->pid, &data->status, 0);*/
	/*signal(SIGINT, handle_sigint);*/
	/*if (WIFSIGNALED(data->status) && WTERMSIG(data->status) == SIGINT)*/
	/*	write(STDOUT_FILENO, "\n", 1);*/
}

static void	loop_exec(t_data *data, t_exec *exec)
{
	while (exec)
	{
		if (exec_len(exec) > 1 || exec->type == CMD)
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

	/*exit_status = 0;*/
	exec = data->exec;
	/*print_exec(exec);*/
	loop_exec(data, exec);
	add_history(data->line);
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
	/*while ((wait_status = wait(&exit_status)) > 0)*/
	/*	check_exit_status(data, exit_status);*/
	(clean_exec(data), ft_free(&data->line));
}
