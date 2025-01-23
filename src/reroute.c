/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reroute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:41:48 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/23 16:23:38 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	rerouteinfile(t_data *data, t_exec *exec)
{
	int	fd;

	/*while (exec->in && exec->in->next)*/
	/*	exec->in = exec->in->next;*/
	/*ft_printerr("rerouteinfile\n");*/
	fd = open(exec->in->file, O_RDONLY);
	if (fd == -1)
	{
		/*ft_putstr_fd("minishell: ", STDERR_FILENO);*/
		/*ft_putstr_fd(exec->in->file, STDERR_FILENO);*/
		/*ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);*/
		ft_printerr("minishell: %s: No such file or directory\n", exec->in->file);
		bruh(data, NULL, 1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (exec->in->type == HEREDOC)
		unlink(exec->in->file);
}

static void	rerouteoutfile(t_data *data, t_exec *exec)
{
	int fd;

	fd = 0;
	/*fd = checkfile(exec->out->file);*/
	/*ft_printerr("rerouteoutfile\n");*/
	if (exec->out->type == REPLACE && fd == 0)
		fd = open(exec->out->file, O_CREAT | O_TRUNC | O_RDWR, 0664);
	else if (fd == 0)
		fd = open(exec->out->file, O_CREAT | O_APPEND | O_RDWR, 0664);
	if (fd == -1)
	{
		ft_printerr("minishell: %s: No such file or directory\n", exec->out->file);
		data->status = 1;
		bruh(data, NULL, 1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	rerouteinpipe(t_exec *exec)
{
	/*ft_printerr("rerouteinpipe\n");*/
	close(exec->prev->pipe[WR]);
	dup2(exec->prev->pipe[RD], STDIN_FILENO);
	close(exec->prev->pipe[RD]);
}

static void	rerouteoutpipe(t_exec *exec)
{
	/*ft_printerr("rerouteoutpipe\n");*/
	close(exec->pipe[RD]);
	dup2(exec->pipe[WR], STDOUT_FILENO);
	close(exec->pipe[WR]);
}

void	reroute(t_data *data, t_exec *exec)
{
	t_input		*in;
	t_output	*out;

	in = exec->in;
	out = exec->out;
	while (exec->in && (exec_len(exec) > 1 || exec->type == CMD))
		(rerouteinfile(data, exec), exec->in = exec->in->next);
	exec->in = in;
	while (exec->out)
		(rerouteoutfile(data, exec), exec->out = exec->out->next);
	exec->out = out;
	if (!exec->in && exec->prev)
		rerouteinpipe(exec);
	if (!exec->out && exec->next)
		rerouteoutpipe(exec);
}
