/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:35:55 by oohnivch          #+#    #+#             */
/*   Updated: 2025/03/03 10:20:15 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// data->token needs to be setup to the current token
void	init_exec_data(t_data *data)
{
	t_exec		*exec;
	t_token		*token;

	add_exec(data);
	exec = data->exec;
	token = data->token;
	while (token)
	{
		if (token->type != WORD && token->type != PIPE)
			add_redir(data, exec, token);
		else if (token->type == PIPE)
			return ((data->token = token->next), (init_exec_data(data)));
		else
			add_to_av_list(data, exec, token);
		token = token->next;
	}
}

void	init_cmd(t_data *data, t_exec *exec)
{
	int	i;

	i = 0;
	if (!exec->av || !exec->av[0])
		bruh(data, "No argv in exec for cmd\n", 1);
	exec->cmd = ft_strdup(exec->av[i]);
	if (!exec->cmd)
		bruh(data, "Failed to allocate memory for cmd", 69);
	check_for_builtin(exec);
	if (exec->type == CMD)
	{
		parse_path(data);
		set_cmd_path(data, exec);
	}
}

void	init_argv(t_data *data, t_exec *exec)
{
	size_t		i;
	size_t		len;

	i = -1;
	len = av_list_len(exec->av_list);
	exec->av = ft_calloc(len + 1 + (len == 0), sizeof(char *));
	if (!exec->av)
		bruh(NULL, "Malloc failed exec_init.c:171", 69);
	if (!len)
	{
		exec->av[0] = ft_strdup("");
		if (!exec->av[0])
			bruh(data, "Malloc failed exec_init.c:171", 69);
		return ;
	}
	exec->av_list = first_av_list(exec->av_list);
	while (exec->av_list && ++i < len)
	{
		exec->av[i] = ft_strdup(exec->av_list->arg);
		if (!exec->av[i])
			bruh(data, "Malloc failed exec_init.c:171", 69);
		if (!exec->av_list->next)
			break ;
		exec->av_list = exec->av_list->next;
	}
}

void	init_exec(t_data *data)
{
	t_exec	*exec;

	if (!data->token)
		return ;
	init_exec_data(data);
	while (data->exec && data->exec->prev)
		data->exec = data->exec->prev;
	exec = data->exec;
	while (exec)
	{
		if (exec->av_list)
		{
			init_argv(data, exec);
			free_av_list(exec);
			init_cmd(data, exec);
		}
		exec->redir = get_first_redir(exec->redir);
		exec = exec->next;
	}
}
