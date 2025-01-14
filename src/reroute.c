/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reroute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:41:48 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/14 17:41:52 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Redirection types:
//	 - in file & out file
//	 - in file & out pipe
//	 - in pipe & out file
//	 - in pipe & out pipe
//	 - in file
//	 - out file
//	 - in pipe
//	 - out pipe
// in redirection:
//	 - read from file
//	 - read from pipe
//	 - read from STDIN_FILENO
// out redirection:
//   - write to file
//   - write to pipe
//   - write to STDOUT_FILENO

static void	rerouteinfile(t_data *data, t_exec *exec)
{
	int	fd;

	while (exec->in && exec->in->next)
		exec->in = exec->in->next;
	fd = open(exec->in->file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(exec->in->file, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory INPUT\n", STDERR_FILENO);
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
	if (exec->out->type == REPLACE && fd == 0)
	{
		ft_putstr_fd("creating + tuncating", STDERR_FILENO);
		fd = open(exec->out->file, O_CREAT | O_TRUNC | O_RDWR, 0664);
	}
	else if (fd == 0)
	{
		ft_putstr_fd("creating + tuncating", STDERR_FILENO);
		fd = open(exec->out->file, O_CREAT | O_APPEND | O_RDWR, 0664);
	}
	if (fd == -1)
	{
		ft_putstr_fd("REROUTE FAILED OUT: ", STDERR_FILENO);
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(exec->out->file, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory OUTPUT\n", STDERR_FILENO);
		data->status = 1;
		bruh(data, NULL, 1);
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
	if (exec->in && (exec_len(exec) > 1 || exec->type == CMD))
		rerouteinfile(data, exec);
	if (exec->out)
		rerouteoutfile(data, exec);
	if (!exec->in && exec->prev)
		rerouteinpipe(exec);
	if (!exec->out && exec->next)
		rerouteoutpipe(exec);
}
