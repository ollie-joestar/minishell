/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:54:00 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/07 14:20:46 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_exec(t_data *data, t_execcmd *ecmd)
{
	if (ecmd->argv[0] == 0)
		bruh(data, "cmd is null\n", 1);
	execve(ecmd->argv[0], ecmd->argv, data->ev);
	bruh(data, "exec failed\n", 1);
}

void	exec_redir(t_data* data, t_redircmd *rcmd)
{
	close(rcmd->fd);
	if (open(rcmd->file, rcmd->mode) < 0)
	{
		ft_putstr_fd("open ", 2);
		ft_putstr_fd(rcmd->file, 2);
		bruh(data, "failed\n", 1);
	}
	runcmd(data, rcmd->cmd);
}

void exec_pipe(t_data* data, t_pipecmd *pcmd)
{
	int p[2];

	if (pipe(p) < 0)
		bruh(data, "pipe failed\n", 1);
	if (fork1(data) == 0)
	{
		close(1);
		dup(p[1]);
		close(p[0]);
		close(p[1]);
		runcmd(data, pcmd->left);
	}
	if (fork1(data) == 0)
	{
		close(0);
		dup(p[0]);
		close(p[0]);
		close(p[1]);
		runcmd(data, pcmd->right);
	}
	close(p[0]);
	close(p[1]);
	wait(0);
	wait(0);

}

void exec_list(t_data* data, t_listcmd *lcmd)
{
	if (fork1(data) == 0)
		runcmd(data, lcmd->left);
	wait(0);
	runcmd(data, lcmd->right);
}

void exec_back(t_data* data, t_backcmd *bcmd)
{
	if (fork1(data) == 0)
		runcmd(data, bcmd->cmd);
}
