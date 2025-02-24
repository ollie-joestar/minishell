/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:09:38 by oohnivch          #+#    #+#             */
/*   Updated: 2025/02/24 17:13:07 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_exec(t_data *data)
{
	t_exec	*exec;

	exec = ft_calloc(1, sizeof(t_exec));
	if (!exec)
		bruh(data, "Failed to allocate memory for exec", 69);
	exec->type = CMD;
	if (data->exec)
	{
		data->exec->next = exec;
		exec->prev = data->exec;
	}
	data->exec = exec;
}

void	add_redir(t_data *data, t_exec *exec, t_token *token)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		bruh(data, "Malloc failed exec_init.c:80", 69);
	redir->type = token->type;
	redir->file = ft_strdup(token->word);
	if (!redir->file)
	{
		free(redir);
		redir = NULL;
		bruh (data, "Malloc failed exec_init.c:87", 69);
	}
	if (exec->redir)
	{
		exec->redir->next = redir;
		redir->prev = exec->redir;
	}
	exec->redir = redir;
}

void	check_for_builtin(t_exec *exec)
{
	if (!ft_strncmp(exec->cmd, "echo", 5) || \
		!ft_strncmp(exec->cmd, "cd", 3) || \
		!ft_strncmp(exec->cmd, "pwd", 4) || \
		!ft_strncmp(exec->cmd, "export", 7) || \
		!ft_strncmp(exec->cmd, "unset", 6) || \
		!ft_strncmp(exec->cmd, "env", 4) || \
		!ft_strncmp(exec->cmd, "exit", 5))
		exec->type = BUILTIN;
	else
		exec->type = CMD;
}

size_t	av_list_len(t_avlist *av_list)
{
	size_t	len;

	if (!av_list)
		return (0);
	len = 0;
	while (av_list->prev)
		av_list = av_list->prev;
	while (av_list)
	{
		av_list = av_list->next;
		len++;
	}
	return (len);
}
