/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reroute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:41:48 by oohnivch          #+#    #+#             */
/*   Updated: 2025/02/25 13:15:12 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	rerouteinfile(t_data *data, t_exec *exec)
{
	int	fd;

	fd = open(exec->redir->file, O_RDONLY);
	if (fd == -1)
	{
		mspe(exec->redir->file);
		data -> status = 1;
		if (lpid(data) == 0)
		{
			(close_pipe_exec(data, exec), close_pipe_exec(data, exec->prev));
			(restore_stds(exec), bruh(data, NULL, 1));
		}
		else
			restore_stds(exec);
		return ;
	}
	if (exec_len(exec) > 1 || exec->type == CMD)
		dup2(fd, STDIN_FILENO);
	close(fd);
	close_pipe_exec(data, exec->prev);
	if (exec->redir->type == HEREDOC)
		unlink(exec->redir->file);
}

static void	rerouteoutfile(t_data *data, t_exec *exec)
{
	int	fd;

	fd = 0;
	if (exec->redir->type == REPLACE && fd == 0)
		fd = open(exec->redir->file, O_CREAT | O_TRUNC | O_RDWR, 0664);
	else if (fd == 0)
		fd = open(exec->redir->file, O_CREAT | O_APPEND | O_RDWR, 0664);
	if (fd == -1)
	{
		mspe(exec->redir->file);
		data->status = 1;
		if (lpid(data) == 0)
		{
			(close_pipe_exec(data, exec), close_pipe_exec(data, exec->prev));
			(restore_stds(exec), bruh(data, NULL, 1));
		}
		else
			restore_stds(exec);
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	rerouteinpipe(t_exec *exec)
{
	close(exec->prev->pipe[WR]);
	dup2(exec->prev->pipe[RD], STDIN_FILENO);
	close(exec->prev->pipe[RD]);
}

static void	rerouteoutpipe(t_exec *exec)
{
	close(exec->pipe[RD]);
	dup2(exec->pipe[WR], STDOUT_FILENO);
	close(exec->pipe[WR]);
}

void	reroute(t_data *data, t_exec *exec)
{
	t_redir		*redir;
	t_exec		*restore;

	if (data->exec == exec)
		restore = exec;
	else
		restore = NULL;
	while (exec->redir && exec->redir->prev)
		exec->redir = exec->redir->prev;
	redir = exec->redir;
	while (exec->redir)
	{
		if (exec->redir->type == INPUT || exec->redir->type == HEREDOC)
			rerouteinfile(data, exec);
		else if (exec->redir->type == REPLACE || exec->redir->type == APPEND)
			rerouteoutfile(data, exec);
		exec->redir = exec->redir->next;
	}
	exec->redir = redir;
	if (!has_input(exec) && exec->prev)
		rerouteinpipe(exec);
	if (!has_output(exec) && exec->next)
		rerouteoutpipe(exec);
	if (restore)
		data->exec = restore;
}
