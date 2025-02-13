/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:49:02 by oohnivch          #+#    #+#             */
/*   Updated: 2025/02/13 15:47:19 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_pipe_exec(t_data *data, t_exec *exec)
{
	if (!exec)
		return ;
	/*mspec2(exec->cmd, "open_pipe_exec\n");*/
	if (pipe(exec->pipe) == -1)
		bruh(data, "pipe failed\n", 1);
	exec->piped = 1;
}

void	close_pipe_exec(t_data *data, t_exec *exec)
{
	int	check1;
	int	check2;

	if (!exec)
		return (mspec("\tclose_pipe_exec NO EXEC\n"));
	if (!exec->piped)
		/*return (mspec2(exec->cmd, "close_pipe_exec NOT PIPED\n"));*/
		return ;
	if (!data)
		bruh(data, "BRO, WHERE'S THE FUCKING DATA?", 1);
	/*if (exec->next)*/
	/*	mspec2(exec->cmd, "close_pipe_exec MIDDLE\n");*/
	/*else*/
	/*	mspec2(exec->cmd, "close_pipe_exec LAST\n");*/
	check1 = safe_close(exec->pipe[RD]);
	check2 = safe_close(exec->pipe[WR]);
	exec->piped = 0;
	if (check1 == -1 || check2 == -1)
		bruh(data, "close_pipe_exec FAILED\n", 1);
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
