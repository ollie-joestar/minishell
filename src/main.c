/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:38:58 by oohnivch          #+#    #+#             */
/*   Updated: 2024/10/24 12:08:57 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>

int MAXLINE = 1024;
char prompt[] = "minishell> ";

#define MAXARGS 128

struct command
{
	int	argc;
	char *argv[MAXARGS];
	enum builtin_t { NONE, QUIT, JOBS, BG, FG } builtin;
};

void	runSystemCommand(struct command *cmd, int bg)
{
	pid_t pid;
	int status;

	if ((pid = fork()) < 0)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
	{
		execvp(cmd->argv[0], cmd->argv);
		perror("execvp");
		exit(1);
	}
	else
		if (bg)
			printf("Child running in background [%d]\n", pid);
		else
			wait(&pid);
}

void	runBuiltinCommand(struct command *cmd, int bg)
{
	if (cmd->builtin == QUIT)
		exit(0);
	else if (cmd->builtin == JOBS)
		printf("JOBS\n");
	else if (cmd->builtin == BG)
		printf("BG\n");
	else if (cmd->builtin == FG)
		printf("FG\n");
}

int	parseBuiltin(struct command *cmd)
{
	if (strcmp(cmd->argv[0], "quit") == 0)
		return QUIT;
	else if (strcmp(cmd->argv[0], "jobs") == 0)
		return JOBS;
	else if (strcmp(cmd->argv[0], "bg") == 0)
		return BG;
	else if (strcmp(cmd->argv[0], "fg") == 0)
		return FG;
	else
		return NONE;
}

int	parse(char *cmdline, struct command *cmd)
{
	static char array[1024];
	const char delims[10] = " \t\r\n";
	char *line = array;
	char *token;
	char *endline;
	int	is_bg = 0;

	(void) strncpy(line, cmdline, MAXLINE);
	endline = line + strlen(line);
	cmd->argc = 0;

	while (line < endline)
	{
		line += strspn(line, delims);
		if (line >= endline)
			break;
		token = line + strcspn(line, delims);
		*token = '\0';

		cmd->argv[cmd->argc++] = line;
		if (cmd->argc == MAXARGS - 1)
			break;
		line = token + 1;
	}

	cmd->argv[cmd->argc] = NULL;
	if (cmd->argc == 0)
		return -1;
	cmd->builtin = parseBuiltin(cmd);

	if ((is_bg = (*cmd->argv[cmd->argc - 1] == '&')) != 0)
		cmd->argv[--cmd->argc] = NULL;

	return is_bg;
}

void	eval(char *cmdline)
{
	int bg;
	struct command cmd;

	bg = parse(cmdline, &cmd);
	if (bg == -1)
	{
		printf("Error parsing the command\n");
		return;
	}
	if (cmd.argv[0] == NULL)
		return;
	if (cmd.builtin == NONE)
		runSystemCommand(&cmd, bg);
	else
		runBuiltinCommand(&cmd, bg);
}

int main(int argc, char **argv, char **envp)
{
	char cmdline[MAXLINE];

	int e = 0;
	get_next_line(1, &e);

	while (1)
	{
		printf("%s", prompt);

		if (fgets(cmdline, MAXLINE, stdin) == NULL && ferror(stdin))
			exit(1);

		if (feof(stdin))
		{
			printf("\n");
			exit(0);
		}
		cmdline[strlen(cmdline) - 1] = '\0';
		eval(cmdline);
	}
}
