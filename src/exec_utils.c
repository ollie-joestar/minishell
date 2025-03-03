/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:36:19 by oohnivch          #+#    #+#             */
/*   Updated: 2025/03/03 16:36:21 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!exec)
		return ;
	if (!exec->piped)
		return ;
	if (!data)
		bruh(data, "BRO, WHERE'S THE FRICKING DATA?", 1);
	close(exec->pipe[RD]);
	close(exec->pipe[WR]);
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

void	failed_cmd_full(t_data *data, t_exec *exec)
{
	struct stat	file_stat;

	if (0 == access(exec->cmd, F_OK))
	{
		if (stat(exec->cmd, &file_stat) == 0)
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
