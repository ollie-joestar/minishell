/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_create_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:29:01 by hanjkim           #+#    #+#             */
/*   Updated: 2025/03/05 22:08:20 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Add a token to the end of the token list
void	add_token_to_end(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!head || !new_token)
		return ;
	if (!*head)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_token;
	new_token->prev = current;
}

// Birth a token from the input string
void	parse_make_token(t_data *data, char *input, int *start, int *end)
{
	t_token	*new_token;

	skip_spaces(input, start);
	*end = *start;
	if (input[*start] == '\0')
		return ;
	new_token = parse_word_token(input, start, data);
	if (!new_token)
		bruh(data, "Failed to allocate memory for token", 2);
	add_token_to_end(&(data->token), new_token);
	*end = *start;
}

// Create an empty shell of a placeholder token
t_token	*create_empty_token(void)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->word = NULL;
	new_token->segments = NULL;
	new_token->type = WORD;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}
