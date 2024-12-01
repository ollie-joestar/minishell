/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:49:14 by hanjkim           #+#    #+#             */
/*   Updated: 2024/12/01 17:08:39 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_redirection(t_data *data, t_token **token)
{
	t_token	*redirection_token;
	t_token	*filename;
	char	*temp_word;
	bool	expand_variables;

	redirection_token = NULL;
	filename = NULL;
	temp_word = NULL;
	redirection_token = *token;
	filename = redirection_token->next;
	if (!filename)
		bruh(data, "Expected filename after redirection", 1);
	if (redirection_token->prev)
		redirection_token->prev->next = filename;
	filename->prev = redirection_token->prev;
	*token = filename;
	if (redirection_token->type == HEREDOC)
	{
		expand_variables = !(filename->quote && filename->single_or_double);
		temp_word = filename->word;
		filename->word = here_doc(data, filename->word);
		ft_free(&temp_word);
	}
	free_token_node(&redirection_token);
}

void	expand_tokens(t_data *data)
{
	t_token	*current;
	char	*expanded_word;

	current = data->token;
	expanded_word = NULL;
	while (current != NULL)
	{
		if (!current->quote || current->single_or_double)
		{
			expanded_word = expand(data, current->word);
			if (expanded_word != NULL)
			{
				free(current->word);
				current->word = expanded_word;
			}
		}
		if (current->type != WORD && current->type != PIPE)
		{
			process_redirection(data, &current);
			continue ;
		}
		current = current->next;
	}
}

void	process_tokens(t_data *data)
{
	t_token	*token;

	token = NULL;
	if (!data->token)
		bruh(data, "No tokens available for processing", 1);
	while (data->token != NULL && data->token->prev != NULL)
		data->token = data->token->prev;
	expand_tokens(data);
}
