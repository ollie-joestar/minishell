/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:49:02 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/20 14:58:33 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	safe_close(int fd)
{
	if (fd == -1)
		ft_putstr_fd("Tried to close invalid fd\n", 2);
	if (fd == 0)
		ft_putstr_fd("Tried to close stdin\n", 2);
	if (fd == 1)
		ft_putstr_fd("Tried to close stdout\n", 2);
	if (fd == 2)
		ft_putstr_fd("Tried to close stderr\n", 2);
	if (fd > 2)
	{
		if (-1 == close(fd))
		{
			ft_putstr_fd("Failed to close fd ", 2);
			ft_putnbr_fd(fd, 2);
			ft_putchar_fd('\n', 2);
		}
	}
}

void	reset_stds(int	stdin_copy, int	stdout_copy)
{
	safe_close(STDIN_FILENO);
	safe_close(STDOUT_FILENO);
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	safe_close(stdin_copy);
	safe_close(stdout_copy);
}

void	check_exit_status(t_data *data, int exit_status)
{
	if (WIFEXITED(exit_status))
		data->status = WEXITSTATUS(exit_status);
	else if (WIFSIGNALED(exit_status))
		data->status = WTERMSIG(exit_status) + 128;
}

int	fork1(t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		bruh(data, "spoons!!!!!\n", 1);
	return (pid);
}

void	open_pipe_exec(t_data *data, t_exec *exec)
{
	if (!exec)
		return ;
	if (pipe(exec->pipe) == -1)
		bruh(data, "pipe failed\n", 1);
	exec->piped = 1;
}

void	close_pipe_exec(t_data *data, t_exec *exec)
{
	if (!exec || !data || !exec->piped)
		return ;
	safe_close(exec->pipe[RD]);
	safe_close(exec->pipe[WR]);
	exec->piped = 0;
}
