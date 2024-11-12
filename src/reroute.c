/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reroute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:41:48 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/12 16:06:49 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Redirection types:
//	 - input file & output file
//	 - input file & output pipe
//	 - input pipe & output file
//	 - input pipe & output pipe
//	 - input file
//	 - output file
//	 - input pipe
//	 - output pipe
// Input redirection:
//	 - read from file
//	 - read from pipe
//	 - read from STDIN_FILENO
// Output redirection:
//   - write to file
//   - write to pipe
//   - write to STDOUT_FILENO

static void	rerouteinfile(t_data *data)
{
	int	fd;

	fd = open(data->exec->input->file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(data->exec->input->file, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	rerouteoutfile(t_data *data)
{
	int fd;

	if (data->exec->output->type == REPLACE)
		fd = open(data->exec->output->file, O_CREAT | O_TRUNC | O_RDWR, 0664);
	else
		fd = open(data->exec->output->file, O_CREAT | O_APPEND | O_RDWR, 0664);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(data->exec->output->file, STDERR_FILENO);
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
	if (data->exec->input)
		rerouteinfile(data);
	if (data->exec->output)
		rerouteoutfile(data);
	if (!data->exec->input && data->exec->prev)
		rerouteinpipe(data);
	if (!data->exec->output && data->exec->next)
		rerouteoutpipe(data);
}
