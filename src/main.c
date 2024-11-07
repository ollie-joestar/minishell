/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:38:58 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/07 10:18:37 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char prompt[] = "minishell> ";

void	runcmd(t_data *data, struct s_cmd *cmd)
{
	int p[2];
	struct s_backcmd *bcmd;
	struct s_execcmd *ecmd;
	struct s_listcmd *lcmd;
	struct s_pipecmd *pcmd;
	struct s_redircmd *rcmd;

	if (cmd == 0)
		exit(1);
	if (cmd->type == EXEC)
	{
		ecmd = (struct s_execcmd*)cmd;
		if (ecmd->argv[0] == 0)
			exit(1);
		execvp(ecmd->argv[0], ecmd->argv);
		bruh(data, "exec failed\n", 1);
	}
	else if (cmd->type == REDIR)
	{
		rcmd = (struct s_redircmd*)cmd;
		close(rcmd->fd);
		if (open(rcmd->file, rcmd->mode) < 0)
		{
			ft_putstr_fd("open ", 2);
			ft_putstr_fd(rcmd->file, 2);
			bruh(data, "failed\n", 1);
		}
		runcmd(data, rcmd->cmd);
	}
	else if (cmd->type == PIPE)
	{
		pcmd = (struct s_pipecmd*)cmd;
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
	else if (cmd->type == LIST)
	{
		lcmd = (struct s_listcmd*)cmd;
		if (fork1(data) == 0)
			runcmd(data, lcmd->left);
		wait(0);
		runcmd(data, lcmd->right);
	}
	else if (cmd->type == BACK)
	{
		bcmd = (struct s_backcmd*)cmd;
		if (fork1(data) == 0)
			runcmd(data, bcmd->cmd);
	}
	else
		bruh(data, "unknown runcmd\n", 1);
	exit(0);
}

int main(int argc, char **argv, char **envp)
{
	static char buf[1024];
	t_data *data;

	data = ft_calloc(1, sizeof(t_data));

	while (getcmd(buf, sizeof(buf)) >= 0)
	{
		ft_printf("%s", prompt);
		if (fork1(data) == 0)
			runcmd(parsecmd(buf));
		wait(0);
	}
	exit(0);
}
