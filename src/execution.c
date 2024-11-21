/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:54:00 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/21 11:53:51 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command(t_data *data, t_exec *exec)
{
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

static void	reset_stdout(int	stdout_copy)
{
	safe_close(STDOUT_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	safe_close(stdout_copy);
}

void	builtin(t_data *data, t_exec *exec)
{
	int32_t	stdout_copy;

	stdout_copy = 1;
	if (exec_len(exec) == 1)
		(stdout_copy = dup(STDOUT_FILENO), reroute(exec));
	if (!(ft_strncmp(exec->av[0], "exit", 5)))
		ft_exit(data, exec);
	else if (!(ft_strncmp(exec->av[0], "echo", 5)))
		echo(data, exec);
	else if (!(ft_strncmp(exec->av[0], "cd", 3)))
		cd(data, exec);
	else if (!(ft_strncmp(exec->av[0], "env", 4)))
		print_env(data);
	else if (!(ft_strncmp(exec->av[0], "pwd", 4)))
		pwd(data, exec);
	else
		bruh(data, "command not found\n", 127);
	if (exec_len(exec) > 1)
		bruh(data, NULL, 0);
	reset_stdout(stdout_copy);
}

void	do_stuff(t_data *data, t_exec *exec)
{
	/*ft_printf("Doing stuff with %s\n", exec->av[0]);*/
	/*ft_printf("\topening pipe\n");*/
	if (exec->next)
		open_pipe_exec(data, exec);
	/*ft_printf("\tforking\n");*/
	data->pid = fork1(data);
	if (data->pid == 0)
	{
		reroute(exec);
		if (exec->type == CMD)
			command(data, exec);
		else
			builtin(data, exec);
	}
	/*ft_printf("\tclosing pipe\n");*/
	close_pipe_exec(data, exec->prev);
	if (!exec->next)
	{
		/*ft_printf("\tclosing last pipe\n");*/
		close_pipe_exec(data, exec);
	}
}

void	run(t_data *data)
{
	t_exec	*exec;
	int		exit_status;
	int		wait_status;

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
	wait_status = 1;
	while (wait_status > 0 && wait_status != data->pid)
		wait_status = wait(&exit_status);
	check_exit_status(data, exit_status);
	while (wait(NULL) > 0)
		;
	/*ft_printf("\nCleaning up...\n");*/
	clean_exec(data);
	ft_free(&data->line);
	/*ft_printf("\nBack to main loop->\n");*/
}
