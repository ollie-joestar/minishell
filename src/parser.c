/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:49:14 by hanjkim           #+#    #+#             */
/*   Updated: 2024/12/02 19:30:07 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_redirection(t_data *data, t_token **token)
{
	t_token	*redirection_token;
	t_token	*filename_token;
	char	*temp_word;
	bool	expand_variables;

	/*redirection_token = NULL;*/
	/*filename = NULL;*/
	/*temp_word = NULL;*/
	redirection_token = *token;
	filename_token = redirection_token->next;
	if (!filename_token)
		bruh(data, "Expected filename after redirection", 2);
	filename_token->type = redirection_token->type;
	if (redirection_token->prev)
		redirection_token->prev->next = filename_token;
	filename_token->prev = redirection_token->prev;
	/**token = filename_token;*/
	if (redirection_token->type == HEREDOC)
	{
		expand_variables = !(filename_token->quote && filename_token->single_or_double);
		temp_word = filename_token->word;
		filename_token->word = here_doc(data, filename_token->word);
		ft_free(&temp_word);
	}
	free_token_node(&redirection_token);
	data->token = filename_token;
	*token = filename_token;
	/*free_old_token(redirection_token);*/
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
			process_redirection(data, &current);
		current = current->next;
	}
}

void	process_tokens(t_data *data)
{
	t_token	*token;

	token = NULL;
	if (!data->token)
		bruh(data, "No tokens available for processing", 2);
	while (data->token != NULL && data->token->prev != NULL)
		data->token = data->token->prev;
	expand_tokens(data);
	while (data->token->prev != NULL)
		data->token = data->token->prev;
}
