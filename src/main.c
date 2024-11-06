/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:38:58 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/06 15:21:38 by oohnivch         ###   ########.fr       */
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
		bruh("exec failed\n");
	}
	else if (cmd->type == REDIR)
	{
		rcmd = (struct s_redircmd*)cmd;
		close(rcmd->fd);
		if (open(rcmd->file, rcmd->mode) < 0)
		{
			ft_putstr_fd("open ", 2);
			ft_putstr_fd(rcmd->file, 2);
			bruh(" failed\n");
		}
		runcmd(rcmd->cmd);
	}
	else if (cmd->type == PIPE)
	{
		pcmd = (struct s_pipecmd*)cmd;
		if (pipe(p) < 0)
			bruh("pipe failed\n");
		if (fork1(data) == 0)
		{
			close(1);
			dup(p[1]);
			close(p[0]);
			close(p[1]);
			runcmd(pcmd->left);
		}
		if (fork1(data) == 0)
		{
			close(0);
			dup(p[0]);
			close(p[0]);
			close(p[1]);
			runcmd(pcmd->right);
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
			runcmd(lcmd->left);
		wait(0);
		runcmd(lcmd->right);
	}
	else if (cmd->type == BACK)
	{
		bcmd = (struct s_backcmd*)cmd;
		if (fork1(data) == 0)
			runcmd(bcmd->cmd);
	}
	else
		bruh("unknown runcmd\n");
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
