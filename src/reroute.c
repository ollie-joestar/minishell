/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reroute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:41:48 by oohnivch          #+#    #+#             */
/*   Updated: 2025/03/03 10:49:15 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	rerouteinfile(t_data *data, t_exec *exec)
{
	int	fd;
	int	check;

	check = 0;
	fd = open(exec->redir->file, O_RDONLY);
	if (fd == -1)
	{
		mspe(exec->redir->file);
		data -> status = 1;
		if (lpid(data) == 0)
		{
			(close_pipe_exec(data, exec), close_pipe_exec(data, exec->prev));
			(restore_stds(data, exec), bruh(data, NULL, 1));
		}
		else
			restore_stds(data, exec);
		return ;
	}
	if (exec_len(exec) > 1 || exec->type == CMD)
		check = dup2(fd, STDIN_FILENO);
	close(fd);
	if (exec->redir->type == HEREDOC)
		unlink(exec->redir->file);
	if (check == -1)
		bruh(data, "Failed to dup2 input file", 1);
}

static void	rerouteoutfile(t_data *data, t_exec *exec)
{
	int	fd;
	int	check;

	fd = 0;
	check = 0;
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
			(restore_stds(data, exec), bruh(data, NULL, 1));
		}
		else
			return (restore_stds(data, exec));
	}
	check = dup2(fd, STDOUT_FILENO);
	close(fd);
	if (check == -1)
		bruh(data, "Failed to dup2 output file", 1);
}

static void	rerouteinpipe(t_data *data, t_exec *exec)
{
	int	check;

	check = dup2(exec->prev->pipe[RD], STDIN_FILENO);
	close_pipe_exec(data, exec->prev);
	if (check == -1)
		bruh(data, "Failed to dup2 input pipe", 1);
}

static void	rerouteoutpipe(t_data *data, t_exec *exec)
{
	int	check;

	check = dup2(exec->pipe[WR], STDOUT_FILENO);
	close_pipe_exec(data, exec);
	if (check == -1)
		bruh(data, "Failed to dup2 output pipe", 1);
}

void	reroute(t_data *data, t_exec *exec)
{
	t_redir		*redir;

	while (exec->redir && exec->redir->prev)
		exec->redir = exec->redir->prev;
	redir = exec->redir;
	if (exec->prev)
		rerouteinpipe(data, exec);
	if (exec->next)
		rerouteoutpipe(data, exec);
	while (exec->redir)
	{
		if (exec->redir->type == INPUT || exec->redir->type == HEREDOC)
			rerouteinfile(data, exec);
		else if (exec->redir->type == REPLACE || exec->redir->type == APPEND)
			rerouteoutfile(data, exec);
		exec->redir = exec->redir->next;
	}
	exec->redir = redir;
}
