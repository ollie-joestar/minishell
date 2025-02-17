/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:35:55 by oohnivch          #+#    #+#             */
/*   Updated: 2025/02/17 12:52:19 by oohnivch         ###   ########.fr       */
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
		(data->exec->next = exec, exec->prev = data->exec);
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
	if (!ft_strncmp(exec->cmd, "echo", 5) ||
		!ft_strncmp(exec->cmd, "cd", 3) ||
		!ft_strncmp(exec->cmd, "pwd", 4) ||
		!ft_strncmp(exec->cmd, "export", 7) ||
		!ft_strncmp(exec->cmd, "unset", 6) ||
		!ft_strncmp(exec->cmd, "env", 4) ||
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
	/*while (av_list->arg && !(*av_list->arg))*/
	/*{*/
	/*	if (!av_list->next)*/
	/*		return (0);*/
	/*	av_list = av_list->next;*/
	/*}*/
	while (av_list)
	{
		av_list = av_list->next;
		len++;
	}
	return (len);
}

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
		/*print_token(token);*/
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
	/*int	limit;*/

	i = 0;
	/*limit = ft_arrlen(exec->av);*/
	if (!exec->av || !exec->av[0])
		bruh(data, "No argv in exec for cmd\n", 1);
	/*while (i < limit && !*exec->av[i])*/
	/*	i++;*/
	/*if (i == limit)*/
	/*	exec->cmd = ft_strdup("");*/
	/*else*/
	/*	exec->cmd = ft_strdup(exec->av[i]);*/
	/**/
	exec->cmd = ft_strdup(exec->av[i]);
	if (!exec->cmd)
		bruh(data, "Failed to allocate memory for cmd", 69);
	check_for_builtin(exec);
	if (exec->type == CMD)
	{
		parse_path(data);
		/*ft_printf("exec->cmd: %s\n", exec->cmd);*/
		set_cmd_path(data, exec);
	}
}

void	init_argv(t_data *data, t_exec *exec)
{
	size_t		i;
	size_t		len;
	size_t		flag;

	/*ft_printf("init_argv\n");*/
	i = -1;
	len = av_list_len(exec->av_list);
	flag = len;
	/*ft_printf("len: %i\n", len);*/
	exec->av = ft_calloc(len + 1 + (flag == 0), sizeof(char *));
	if (!exec->av)
		bruh(NULL, "Malloc failed exec_init.c:171", 69);
	if (!flag)
	{
		exec->av[0] = ft_strdup("");
		return ;
	}
	exec->av_list = first_av_list(exec->av_list);
	while (exec->av_list && ++i < len)
	{
		exec->av[i] = ft_strdup(exec->av_list->arg);
		if (!exec->av[i])
			bruh(data, "Malloc failed exec_init.c:171", 69);
		/*ft_printf("exec->av[%i]: %s\n", i, exec->av[i]);*/
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
	/*ft_printf("if i see this, then i need to go for a smoke\n\n\n");*/
	while (data->exec && data->exec->prev)
		data->exec = data->exec->prev;
	exec = data->exec;
	while (exec)
	{
		/*print_exec(exec);*/
		if (exec->av_list)
		{
			init_argv(data, exec);
			free_av_list(exec);
			init_cmd(data, exec);
		}
		/*print_exec(exec);*/
		/*else*/
		/*	ft_printf("No av_list\n");*/
		exec->redir = get_first_redir(exec->redir);
		exec = exec->next;
	}
}
