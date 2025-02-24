/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:33:50 by oohnivch          #+#    #+#             */
/*   Updated: 2025/02/24 16:44:43 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_pids(t_data *data)
{
	t_pidlist	*pid;

	pid = data->pid_list;
	while (pid && pid->prev)
		pid = pid->prev;
	ft_printf("Printing pids\n");
	while (pid)
	{
		ft_printf("[%d]\n", pid->pid);
		pid = pid->next;
	}
}

void	print_token(t_token *token)
{
	t_segment	*seg;

	if (!token)
		return ;
	printf("Printing token\n");
	seg = token->segments;
	ft_printf("\tToken word: %s\n", token->word);
	ft_printf("\tSegments: ");
	while (seg)
	{
		ft_printf("[%s]", seg->text);
		seg = seg->next;
	}
	ft_printf("\n\tType: %d\n", token->type);
	if (token->prev)
		ft_printf("\tPrev: %s\n", token->prev->word);
	else
		ft_printf("\tPrev: NULL\n");
	if (token->next)
		ft_printf("\tNext: %s\n", token->next->word);
	else
		ft_printf("\tNext: NULL\n");
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
}
