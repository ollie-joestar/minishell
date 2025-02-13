/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reroute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:41:48 by oohnivch          #+#    #+#             */
/*   Updated: 2025/02/13 16:33:38 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	rerouteinfile(t_data *data, t_exec *exec)
{
	int	fd;

	/*if (exec_len(exec) == 1 && exec->type != CMD)*/
	/*{*/
	/*	if (exec->redir->type == HEREDOC)*/
	/*		unlink(exec->redir->file);*/
	/*	return ;*/
	/*}*/
	/*while (exec->in && exec->in->next)*/
	/*	exec->in = exec->in->next;*/
	/*mspec2(exec->cmd, "rerouteinfile\n");*/
	/*ft_printerr("name: %s\n", exec->redir->file);*/
	fd = open(exec->redir->file, O_RDONLY);
	if (fd == -1)
	{
		/*ft_putstr_fd(exec->in->file, STDERR_FILENO);*/
		/*ft_putstr_fd("minishell: ", STDERR_FILENO);*/
		/*ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);*/
		mspe(exec->redir->file);
		/*msperror2(exec->redir->file, "No such file or directory");*/
		/*ft_printerr("minishell: %s: No such file or directory\n", exec->redir->file);*/
		data -> status = 1;
		if (lpid(data) == 0)
			bruh(data, NULL, 1);
		return ;
		/*bruh(data, NULL, 1);*/
	}
	if (exec_len(exec) > 1 || exec->type == CMD)
		dup2(fd, STDIN_FILENO);
	close(fd);
	/*dup2(fd, STDIN_FILENO);*/
	if (exec->redir->type == HEREDOC)
		unlink(exec->redir->file);
}

static void	rerouteoutfile(t_data *data, t_exec *exec)
{
	int fd;

	fd = 0;
	/*fd = checkfile(exec->out->file);*/
	/*mspec2(exec->cmd, "rerouteoutfile\n");*/
	/*ft_printerr("name: %s\n", exec->redir->file);*/
	if (exec->redir->type == REPLACE && fd == 0)
		fd = open(exec->redir->file, O_CREAT | O_TRUNC | O_RDWR, 0664);
	else if (fd == 0)
		fd = open(exec->redir->file, O_CREAT | O_APPEND | O_RDWR, 0664);
	if (fd == -1)
	{
		mspe(exec->redir->file);
		/*ft_putstr_fd("minishell: ", STDERR_FILENO);*/
		/*perror(exec->redir->file);*/
		/*ft_printerr("minishell: %s: No such file or directory\n", exec->redir->file);*/
		data->status = 1;
		if (lpid(data) == 0)
			bruh(data, NULL, 1);
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	rerouteinpipe(t_exec *exec)
{
	/*mspec2(exec->cmd, "rerouteinpipe\n");*/
	close(exec->prev->pipe[WR]);
	dup2(exec->prev->pipe[RD], STDIN_FILENO);
	close(exec->prev->pipe[RD]);
}

static void	rerouteoutpipe(t_exec *exec)
{
	/*mspec2(exec->cmd, "rerouteoutpipe\n");*/
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
	/*mspec2(exec->cmd, "REROUTING!\n");*/
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
