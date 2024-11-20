/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:54:00 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/20 16:07:36 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command(t_data *data, t_exec *exec)
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

void	builtin(t_data *data, t_exec *exec)
{
	/*int32_t	stdin_copy;*/
	/*int32_t	stdout_copy;*/
	/**/
	/*stdin_copy = dup(STDIN_FILENO);*/
	/*stdout_copy = dup(STDOUT_FILENO);*/
	if (exec->av[0] == 0)
		bruh(data, "cmd is null\n", 1);
	if (!(ft_strncmp(exec->av[0], "exit", 5)))
	{
		if (exec->av[1])
			bruh(data, "exit", ft_atoi(exec->av[1]));
		bruh(data, "exit", data->status);
	}
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
	/*reset_stds(stdin_copy, stdout_copy);*/
}

void	do_stuff(t_data *data, t_exec *exec)
{
	if (exec->next)
		open_pipe_exec(data, exec);
	data->pid = fork1(data);
	if (data->pid == 0)
	{
		if (exec->type == CMD)
			command(data, exec);
		else
			builtin(data, exec);
	}
	close_pipe_exec(data, exec->prev);
}

void	run(t_data *data)
{
	t_exec	*exec;
	int		exit_status;
	int		wait_status;

	exec = data->exec;
	while(exec)
	{
		if (exec->next || exec->prev || exec->type == CMD)
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
	ft_printf("\nCleaning up...\n");
	clean_exec(data);
	ft_free(&data->line);
	ft_printf("\nBack to main loop->\n");
}
