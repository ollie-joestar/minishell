/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reroute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:41:48 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/18 18:24:47 by hanjkim          ###   ########.fr       */
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

static void	rerouteinfile(t_exec *exec)
{
	int	fd;

	while (exec->in && exec->in->next)
		exec->in = exec->in->next;
	fd = open(exec->in->file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(exec->in->file, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	rerouteoutfile(t_exec *exec)
{
	int fd;

	if (exec->out->type == REPLACE)
		fd = open(exec->out->file, O_CREAT | O_TRUNC | O_RDWR, 0664);
	else
		fd = open(exec->out->file, O_CREAT | O_APPEND | O_RDWR, 0664);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(exec->out->file, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	rerouteinpipe(t_exec *exec)
{
	dup2(exec->prev->pipe[RD], STDIN_FILENO);
	close(exec->prev->pipe[RD]);
	close(exec->prev->pipe[WR]);
}

static void	rerouteoutpipe(t_exec *exec)
{
	dup2(exec->pipe[WR], STDOUT_FILENO);
	close(exec->pipe[RD]);
	close(exec->pipe[WR]);
}

void	reroute(t_exec *exec)
{
	if (exec->in)
		rerouteinfile(exec);
	if (exec->out)
		rerouteoutfile(exec);
	if (!exec->in && exec->prev)
		rerouteinpipe(exec);
	if (!exec->out && exec->next)
		rerouteoutpipe(exec);
}
