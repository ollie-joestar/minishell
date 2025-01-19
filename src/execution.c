/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:35:58 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/19 17:12:59 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command(t_data *data, t_exec *exec)
{
	parse_env_into_ev(data);
	execve(exec->cmd, exec->av, data->ev);
	if (ft_strchr(exec->av[0], '/'))
	{
		if (0 == access(exec->av[0], F_OK))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(exec->cmd, 2);
			bruh(data, ": Permission denied", 126);
		}
		ft_putstr_fd("minishell: no such file or directory: ", 2);
		bruh(data, exec->av[0], 127);
	}
	else
	{
		if (0 == access(exec->av[0], F_OK))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(exec->cmd, 2);
			bruh(data, ": Permission denied", 126);
		}
		ft_putstr_fd("minishell: command not found: ", 2);
		bruh(data, exec->av[0], 127);
	}
}

static void	reset_stdout(int	stdout_copy)
{
	if (stdout_copy == -1 || stdout_copy == STDOUT_FILENO)
		return ;
	dup2(stdout_copy, STDOUT_FILENO);
	safe_close(stdout_copy);
}

void	builtin(t_data *data, t_exec *exec)
{
	int32_t	stdout_copy;

	stdout_copy = -1;
	if (exec_len(exec) == 1)
		(stdout_copy = dup(STDOUT_FILENO), reroute(data, exec));
	if (!(ft_strncmp(exec->av[0], "exit", 5)))
	{
		reset_stdout(stdout_copy);
		ft_exit(data, exec);
	}
	else if (!(ft_strncmp(exec->av[0], "echo", 5)))
		echo(data, exec);
	else if (!(ft_strncmp(exec->av[0], "cd", 3)))
		cd(data, exec);
	else if (!(ft_strncmp(exec->av[0], "env", 4)))
		print_env(data);
	else if (!(ft_strncmp(exec->av[0], "pwd", 4)))
		pwd(data, exec);
	else if (!(ft_strncmp(exec->av[0], "export", 7)))
		export(data, exec);
	else if (!(ft_strncmp(exec->av[0], "unset", 6)))
		unset(data, exec);
	else
		bruh(data, "command not found\n", 127);
	if (exec_len(exec) > 1)
		bruh(data, NULL, 0);
	else if (ft_strncmp(exec->av[0], "exit", 5))
		reset_stdout(stdout_copy);
}

void	do_stuff(t_data *data, t_exec *exec)
{
	if (exec->next)
		open_pipe_exec(data, exec);
	/*signal(SIGINT, SIG_IGN);*/
	data->pid = fork1(data);
	if (data->pid == 0)
	{
		/*signal(SIGINT, SIG_DFL);*/
		reroute(data, exec);
		if (exec->type == CMD)
			command(data, exec);
		else
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

void	run(t_data *data)
{
	t_exec	*exec;
	int		exit_status;
	int		wait_status;

	exit_status = 0;
	while (data->exec->prev)
		data->exec = data->exec->prev;
	exec = data->exec;
	while(exec)
	{
		if (exec_len(exec) > 1 || exec->type == CMD)
			do_stuff(data, exec);
		else
			builtin(data, exec);
		exec = exec->next;
	}
	add_history(data->line);
	if (exec_len(data->exec) > 1 || exec_has_cmd(data->exec))
	{
		wait_status = 1;
		while (wait_status > 0 && wait_status != data->pid)
			wait_status = wait(&exit_status);
		check_exit_status(data, exit_status);
		while (wait(NULL) > 0)
			;
	}
	while ((wait_status = wait(&exit_status)) > 0)
	{
		check_exit_status(data, exit_status);
	}
	/*ft_printf("\nCleaning up...\n");*/
	clean_exec(data);
	ft_free(&data->line);
	/*ft_printf("\nBack to main loop->\n");*/
}
