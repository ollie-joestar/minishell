/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_create_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:29:01 by hanjkim           #+#    #+#             */
/*   Updated: 2024/11/30 00:13:44 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_token_type(t_token *token)
{
	if (token->word == NULL)
		return ;
	if (!(ft_strncmp(token->word, "<", 2)))
		token->type = INPUT;
	else if (!(ft_strncmp(token->word, "<<", 3)))
		token->type = HEREDOC;
	else if (!(ft_strncmp(token->word, ">", 2)))
		token->type = REPLACE;
	else if (!(ft_strncmp(token->word, ">>", 3)))
		token->type = APPEND;
	else if (!(ft_strncmp(token->word, "|", 2)))
		token->type = PIPE;
	else
		token->type = WORD;
}

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

t_token	*create_token(char *str, bool quote, bool single_or_double)
{
	t_token	*new_token;
	char	*dup_str;

	new_token = (t_token *)ft_calloc(1, (sizeof(t_token)));
	if (!new_token)
		return (NULL);
	dup_str = ft_strdup(str);
	if (!dup_str)
		return (free(new_token), NULL);
	new_token->word = dup_str;
	new_token->quote = quote;
	new_token->single_or_double = single_or_double;
	new_token->type = WORD;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}
