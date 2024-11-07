/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:38:58 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/07 12:13:00 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char prompt[] = "minishell> ";

void	runcmd(t_data *data, t_cmd *cmd)
{
	if (cmd == 0)
		bruh(data, "cmd is null\n", 1);
	if (cmd->type == EXEC)
		exec_exec(data, (t_execcmd*)cmd);
	else if (cmd->type == REDIR)
		exec_redir(data, (t_redircmd*)cmd);
	else if (cmd->type == PIPE)
		exec_pipe(data, (t_pipecmd*)cmd);
	else if (cmd->type == LIST)
		exec_list(data, (t_listcmd*)cmd);
	else if (cmd->type == BACK)
		exec_back(data, (t_backcmd*)cmd);
	else
		bruh(data, "unknown runcmd\n", 1);
}

//DELETE THIS WHEN DONE
t_cmd *parsecmd(char *s)
{
	t_cmd *cmd;

	cmd = init_execcmd();
	((t_execcmd*)cmd)->argv[0] = s;
	((t_execcmd*)cmd)->argv[1] = 0;
	return (cmd);
}

//DELETE THIS WHEN DONE
//getcmd is a function that reads a line from the terminal
//and stores it in the buffer
//it returns the number of characters read
int	getcmd(char *buf, int nbuf)
{
	if (isatty(fileno(stdin)))
	{
		fprintf(stdout, "%s", prompt);
	}
	memset(buf, 0, nbuf);
	fgets(buf, nbuf, stdin);
	if (buf[0] == 0)
		return -1;
	return 0;
}

int main(int argc, char **argv, char **envp)
{
	static char buf[1024];
	t_data *data;

	data = ft_calloc(1, sizeof(t_data));

	while (getcmd(buf, sizeof(buf)) >= 0)
	{
		if (fork1(data) == 0)
			runcmd(data, (parsecmd(buf)));
		wait(0);
	}
	bruh(data, NULL, 0);
}
