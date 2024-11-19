/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:10:42 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/19 12:53:49 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *token)
{
	printf("Printing token\n");
	if (!token)
		return ;
	ft_printf("\tToken: %s\n", token->word);
	ft_printf("\tType: %d\n", token->type);
	ft_printf("\tLeft: %s\n", token->left ? token->left->word : "NULL");
	ft_printf("\tRight: %s\n", token->right ? token->right->word : "NULL");
}

void	print_tokens(t_token *token)
{
	int	i;
	if (!token)
	{
		ft_printf("No tokens\n");
		return ;
	}
	while (token && token->left)
		token = token->left;
	/*ft_printf("reset tokens\n");*/
	i = 0;
	while (token)
	{
		ft_printf("Printing token [%d] \n", i);
		print_token(token);
		token = token->right;
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
	ft_printf("\n");
}

void	print_exec(t_exec *exec)
{
	ft_printf("Printing exec\n");
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
	ft_printf("\tInput: %s\n", exec->in ? exec->in->file : "NULL");
	ft_printf("\tOutput: %s\n", exec->out ? exec->out->file : "NULL");
	ft_printf("\tPipe: %d %d\n", exec->pipe[RD], exec->pipe[WR]);
	ft_printf("\tPrev: %s\n", exec->prev ? exec->prev->cmd : "NULL");
	ft_printf("\tNext: %s\n", exec->next ? exec->next->cmd : "NULL");
	print_arr(exec->av);
}

void	print_stds(void)
{
	ft_printf("STDIN: %d\n", dup(STDIN_FILENO));
	ft_printf("STDOUT: %d\n", dup(STDOUT_FILENO));
	ft_printf("STDERR: %d\n", dup(STDERR_FILENO));
}
