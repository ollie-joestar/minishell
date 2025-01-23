/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:49:02 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/23 13:57:49 by oohnivch         ###   ########.fr       */
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

int	exec_has_cmd(t_exec *exec)
{
	t_exec	*tmp;

	tmp = exec;
	while (tmp && tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		if (tmp->type == CMD)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
