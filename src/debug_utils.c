/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:10:42 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/27 14:14:22 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *token)
{
	printf("Printing token\n");
	if (!token)
		return ;
	ft_printf("\tToken word: %s\n", token->word);
	ft_printf("\tSegments: ");
	t_segment	*seg = token->segments;
	while (seg)
	{
		ft_printf("[%s]", seg->text);
		seg = seg->next;
	}
	ft_printf("\n\tType: %d\n", token->type);
	ft_printf("\tPrev: %s\n", token->prev ? token->prev->word : "NULL");
	ft_printf("\tNext: %s\n", token->next ? token->next->word : "NULL");
}

void	print_tokens(t_token *token)
{
	int	i;
	if (!token)
	{
		ft_printf("No tokens\n");
		return ;
	}
	while (token && token->prev)
		token = token->prev;
	/*ft_printf("reset tokens\n");*/
	i = 0;
	while (token)
	{
		ft_printf("Printing token [%d] \n", i);
		print_token(token);
		token = token->next;
		i++;
	}
}

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	ft_printf("Printing array\n");
	if (!arr || !*arr)
		ft_printf("NULL\n");
	while (arr[i])
	{
		ft_printf("\t[%d] %s\n", i, arr[i]);
		i++;
	}
	ft_printf("\t[%d] %s\n", i, NULL);
}

void	print_av_list(t_exec	*exec)
{
	t_avlist	*av_list;

	ft_printf("\tArgv_list:\n");
	if (!exec->av_list)
	{
		ft_printf("\t\tNULL\n");
		return ;
	}
	while (exec->av_list->prev)
		exec->av_list = exec->av_list->prev;
	av_list = exec->av_list;
	while (av_list)
	{
		ft_printf("\t\t[%s]\n", av_list->arg);
		av_list = av_list->next;
	}
	ft_printf("\n");
}

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
	int	i;
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

	i = -1;
	while (exec && exec->prev)
		exec = exec->prev;
	while (exec)
	{
		ft_printf("\nPrinting exec [%d]\n", ++i);
		if (!exec)
		{
			ft_printf("No exec\n");
			return ;
		}
		if (exec->type == CMD)
		{
			ft_printf("\tType: CMD\n");
			ft_printf("\tCommand: %s\n", exec->cmd);
		}
		else
		{
			ft_printf("\tType: BUILTIN\n");
			ft_printf("\tCommand: %s\n", exec->cmd);
		}
		print_redirs(exec);
		ft_printf("\tPipe: %d %d\n", exec->pipe[RD], exec->pipe[WR]);
		ft_printf("\tPrev: %s\n", exec->prev ? exec->prev->cmd : "NULL");
		ft_printf("\tNext: %s\n", exec->next ? exec->next->cmd : "NULL");
		print_av_list(exec);
		print_av(exec);
		if (exec->next)
			exec = exec->next;
		else
			break ;
	}
}

void	print_stds(void)
{
	ft_printf("STDIN: %d\n", dup(STDIN_FILENO));
	ft_printf("STDOUT: %d\n", dup(STDOUT_FILENO));
	ft_printf("STDERR: %d\n", dup(STDERR_FILENO));
}
