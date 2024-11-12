/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reroute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:41:48 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/12 16:19:52 by oohnivch         ###   ########.fr       */
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

static void	rerouteinfile(t_data *data)
{
	int	fd;

	fd = open(data->exec->in->file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(data->exec->in->file, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	rerouteoutfile(t_data *data)
{
	int fd;

	if (data->exec->out->type == REPLACE)
		fd = open(data->exec->out->file, O_CREAT | O_TRUNC | O_RDWR, 0664);
	else
		fd = open(data->exec->out->file, O_CREAT | O_APPEND | O_RDWR, 0664);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(data->exec->out->file, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	rerouteinpipe(t_data *data)
{
	dup2(data->exec->prev->pipe[RD], STDIN_FILENO);
	close(data->exec->prev->pipe[RD]);
	close(data->exec->prev->pipe[WR]);
}

static void	rerouteoutpipe(t_data *data)
{
	dup2(data->exec->pipe[WR], STDOUT_FILENO);
	close(data->exec->pipe[RD]);
	close(data->exec->pipe[WR]);
}

void	reroute(t_data *data)
{
	if (data->exec->in)
		rerouteinfile(data);
	if (data->exec->out)
		rerouteoutfile(data);
	if (!data->exec->in && data->exec->prev)
		rerouteinpipe(data);
	if (!data->exec->out && data->exec->next)
		rerouteoutpipe(data);
}
