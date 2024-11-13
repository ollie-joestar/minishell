/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:38:56 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/13 16:42:25 by oohnivch         ###   ########.fr       */
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

void	add_output(t_exec *exec, t_lex_token *token)
{
	t_output	*output;

	output = ft_calloc(1, sizeof(t_output));
	if (!output)
		return ;
	output->type = token->type;
	output->file = ft_strdup(token->word);
	if (!output->file)
	{
		free(output);
		return ;
	}
	exec->out = output;
}

void	add_input(t_exec *exec, t_lex_token *token)
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

// data->token needs to be setup to the current token
void	init_exec_data(t_data *data)
{
	t_exec		*exec;
	t_lex_token	*token;

	token = data->token;
	while (token)
	{
		exec = new_exec();
		if (!data->exec)
			data->exec = exec;
		else
		{
			data->exec->next = exec;
			exec->prev = data->exec;
			data->exec = exec;
		}
		if (token->type == INPUT)
			add_input(exec, token);
		else if (token->type == REPLACE)
			add_output(exec, token);
		else if (token->type == PIPE)
		{
			data->token = token->right;
			return (init_exec_data(data));
		}
		else 
		{
			exec->av = create_argv(data, token);
			token = data->token;	
		}
		token = token->right;
	}
}
