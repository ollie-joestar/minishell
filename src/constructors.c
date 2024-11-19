/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:38:56 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/19 15:06:06 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec	*new_exec(void)
{
	t_exec	*exec;

	exec = ft_calloc(1, sizeof(t_exec));
	if (!exec)
		return (NULL);
	return (exec);
}

void	add_output(t_exec *exec, t_token *token)
{
	t_output	*output;

	if (!exec->out)
	{
		output = ft_calloc(1, sizeof(t_output));
		if (!output)
			return ;
	}
	else
		output = exec->out;
	output->type = token->type;
	ft_free(&output->file);
	output->file = ft_strdup(token->word);
	if (!output->file)
	{
		free(output);
		return ;
	}
}

void	add_input(t_exec *exec, t_token *token)
{
	t_input	*input;

	input = ft_calloc(1, sizeof(t_input));
	if (!input)
		return ;
	input->type = token->type;
	input->file = ft_strdup(token->word);
	if (!input->file)
	{
		free(input);
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
		bruh(data, "Failed to allocate memory", 1);
	if (exec->av[0] == 0)
		bruh(data, "cmd is null\n", 1);
	exec->cmd = ft_strdup(exec->av[0]);
	check_for_builtin(exec);
	if (exec->type == CMD)
	{
		parse_path(data);
		set_cmd_path(data, exec);
	}
}

// data->token needs to be setup to the current token
void	init_exec_data(t_data *data)
{
	t_exec		*exec;
	t_token		*token;

	token = data->token;
	while (token)
	{
		exec = new_exec();
		if (data->exec)
			(data->exec->next = exec, exec->prev = data->exec);
		data->exec = exec;
		print_token(token);
		if (token->type == INPUT || token->type == HEREDOC)
			add_input(exec, token);
		else if (token->type == REPLACE || token->type == APPEND)
			add_output(exec, token);
		else if (token->type == PIPE)
			return ((data->token = token->right), (init_exec_data(data)));
		else 
			(add_av(data, exec, token), token = data->token);
		token = token->right;
	}
}
