/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:10:42 by oohnivch          #+#    #+#             */
/*   Updated: 2025/02/24 16:42:46 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_av(t_exec	*exec)
{
	int	i;

	i = 0;
	ft_printf("\tArgv:\n");
	if (!exec->av || !*exec->av)
	{
		ft_printf("\t\tNULL\n");
		return ;
	}
	while (exec->av[i])
	{
		ft_printf("\t\t[%d] %s\n", i, exec->av[i]);
		i++;
	}
	ft_printf("\t\t[%d] %s\n", i, NULL);
}

void	print_redirs(t_exec *exec)
{
	int		i;
	t_redir	*redir;

	i = 0;
	ft_printf("\tRedirs:\n");
	redir = exec->redir;
	while (redir)
	{
		ft_printf("\t\t[%d] %s Type: ", i, redir->file);
		if (redir->type == INPUT)
			ft_printf("INPUT\n");
		else if (redir->type == HEREDOC)
			ft_printf("HEREDOC\n");
		else if (redir->type == REPLACE)
			ft_printf("REPLACE\n");
		else if (redir->type == APPEND)
			ft_printf("APPEND\n");
		i++;
		redir = redir->next;
	}
	ft_printf("\t\tNULL\n");
}

void	print_exec(t_exec *exec)
{
	int	i;

	i = 0;
	if (!exec)
		return (mspec("No exec"));
	while (exec && exec->prev)
		exec = exec->prev;
	while (exec)
	{
		print_execution(exec, i);
		if (!exec->next)
			break ;
		exec = exec->next;
		i++;
	}
}

void	print_execution(t_exec *exec, int i)
{
	ft_printf("\n\nPrinting execution [%d]\n", i);
	if (!exec)
		return (mspec("No exec"));
	if (exec->type == CMD)
		ft_printf("\tType: CMD\n");
	else
		ft_printf("\tType: BUILTIN\n");
	ft_printf("\tCommand: %s\n", exec->cmd);
	print_redirs(exec);
	ft_printf("\tPipe: %d %d\n", exec->pipe[RD], exec->pipe[WR]);
	if (exec->prev)
		ft_printf("\tPrev: %s\n", exec->prev->cmd);
	else
		ft_printf("\tPrev: NULL\n");
	if (exec->next)
		ft_printf("\tNext: %s\n", exec->next->cmd);
	else
		ft_printf("\tNext: NULL\n");
	print_av_list(exec);
	print_av(exec);
}

void	print_stds(void)
{
	ft_printf("STDIN: %d\n", dup(STDIN_FILENO));
	ft_printf("STDOUT: %d\n", dup(STDOUT_FILENO));
	ft_printf("STDERR: %d\n", dup(STDERR_FILENO));
}
