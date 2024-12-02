/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:49:02 by oohnivch          #+#    #+#             */
/*   Updated: 2024/12/02 20:12:18 by hanjkim          ###   ########.fr       */
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

size_t	exec_len(t_exec *exec)
{
	size_t	len;
	t_exec	*tmp;

	tmp = exec;
	len = 0;
	while (tmp && tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}
