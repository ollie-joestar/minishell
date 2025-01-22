/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:35:55 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/22 12:33:59 by oohnivch         ###   ########.fr       */
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

void	add_output(t_data *data, t_exec *exec, t_token *token)
{
	t_output	*output;

	output = ft_calloc(1, sizeof(t_output));
	if (!output)
		bruh(data, "Failed to allocate memory for output", 69);
	output->type = token->type;
	output->file = ft_strdup(token->word);
	if (!output->file)
	{
		free(output);
		output = NULL;
		return ;
	}
	if (exec->out)
	{
		exec->out->next = output;
		output->prev = exec->out;
	}
	exec->out = output;
}

void	add_input(t_data *data, t_exec *exec, t_token *token)
{
	t_input	*input;

	input = ft_calloc(1, sizeof(t_input));
	if (!input)
		bruh(data, "Failed to allocate memory for input", 69);
	input->type = token->type;
	input->file = ft_strdup(token->word);
	if (!input->file)
	{
		free(input);
		input = NULL;
		return ;
	}
	if (exec->in)
	{
		exec->in->next = input;
		input->prev = exec->in;
	}
	exec->in = input;
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

void	add_av(t_data *data, t_exec *exec, t_token *token)
{
	exec->av = create_argv(data, token);
	if (!exec->av)
		bruh(data, "Failed to allocate memory", 69);
	/*print_arr(exec->av);*/
	if (!exec->av[0])
		bruh(data, "cmd is null\n", 1);
	exec->cmd = ft_strdup(exec->av[0]);
	if (!exec->cmd)
		bruh(data, "Failed to allocate memory for cmd", 69);
	check_for_builtin(exec);
	if (exec->type == CMD)
	{
		parse_path(data);
		set_cmd_path(data, exec);
	}
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
		len++;
		av_list = av_list->next;
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
		if (token->type == INPUT || token->type == HEREDOC)
			add_input(data, exec, token);
		else if (token->type == REPLACE || token->type == APPEND)
			add_output(data, exec, token);
		else if (token->type == PIPE)
			return ((data->token = token->next), (init_exec_data(data)));
		else 
			add_to_avlist(data, exec, token);
			/*while (token->next && token->next->type == WORD)*/
			/*	token = token->next;*/
		token = token->next;
		/*ft_printf("Next Token");*/
	}
}

void	init_cmd(t_data *data, t_exec *exec)
{
	if (!exec->av || !exec->av[0])
		bruh(data, "No argv in exec for cmd\n", 1);
	exec->cmd = ft_strdup(exec->av[0]);
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
	size_t	i;

	if (!exec || !exec->av_list)
		return ;
	i = 0;
	exec->av = ft_calloc(av_list_len(exec->av_list) + 1, sizeof(char *));
	if (!exec->av)
		bruh(NULL, "Failed to allocate memory for av", 69);
	while (exec->av_list->prev)
		exec->av_list = exec->av_list->prev;
	while (exec->av_list)
	{
		exec->av[i] = ft_strdup(exec->av_list->arg);
		if (!exec->av[i])
		{
			ft_printerr("Failed to allocate memory for av[%d]\n", i);
			bruh(data, NULL, 69);
		}
		exec->av_list = exec->av_list->next;
		i++;
	}
}

void	init_exec(t_data *data)
{
	t_exec	*exec;

	init_exec_data(data);
	/*print_exec(data->exec);*/
	/*ft_printf("if i see this, then i need to go for a smoke\n\n\n");*/
	while (data->exec && data->exec->prev)
		data->exec = data->exec->prev;
	exec = data->exec;
	while (exec)
	{
		if (exec->av_list)
			(init_argv(data, exec), free_av_list(exec), init_cmd(data, exec));
		exec = exec->next;
	}
}
