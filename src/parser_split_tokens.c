/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 20:03:14 by hanjkim           #+#    #+#             */
/*   Updated: 2024/12/02 19:30:38 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_split_vars(t_split_vars *vars)
{
	vars->words = NULL;
	vars->new_head = NULL;
	vars->new_tail = NULL;
	vars->new_token = NULL;
	vars->i = -1;
}

bool	should_split_token(t_token *token)
{
	if (token->type == WORD && token->word != NULL && token->quote == false)
	{
		if (ft_strchr(token->word, ' ') != NULL)
			return (true);
	}
	return (false);
}

void	make_split_tokens(t_split_vars *vars, t_token *original, t_data *data)
{
	while (vars->words[++vars->i] != NULL)
	{
		vars->new_token = create_token(vars->words[vars->i],
				original->quote, original->single_or_double);
		if (!vars->new_token)
		{
			free_arr(&vars->words);
			bruh(data, "Split_tok fail", 2);
		}
		vars->new_token->type = WORD;
		if (!vars->new_head)
		{
			vars->new_head = vars->new_token;
			vars->new_tail = vars->new_token;
		}
		else
		{
			vars->new_tail->next = vars->new_token;
			vars->new_token->prev = vars->new_tail;
			vars->new_tail = vars->new_token;
		}
	}
}

t_token	*split_token(t_token *original_token, t_data *data)
{
	t_split_vars	vars;

	init_split_vars(&vars);
	vars.words = ft_split(original_token->word, ' ');
	if (!vars.words)
		bruh(data, "Failed to split token words", 2);
	make_split_tokens(&vars, original_token, data);
	free_arr(&vars.words);
	return (vars.new_head);
}

void	split_tokens(t_data *data)
{
	t_token		*current_token;
	t_token		*new_tokens_head;

	current_token = NULL;
	new_tokens_head = NULL;
	current_token = data->token;
	data->replacements = NULL;
	while (current_token != NULL)
	{
		if (should_split_token(current_token))
		{
			new_tokens_head = split_token(current_token, data);
			add_replace(data, current_token, new_tokens_head);
		}
		current_token = current_token->next;
	}
}
