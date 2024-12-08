/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_create_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:29:01 by hanjkim           #+#    #+#             */
/*   Updated: 2024/12/08 18:29:00 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_segments(t_token *token)
{
	size_t		total_len;
	char		*joined;
	t_segment	*seg;

	total_len = 0;
	seg = token->segments;
	while (seg)
	{
		total_len += ft_strlen(seg->text);
		seg = seg->next;
	}
	joined = ft_calloc(total_len + 1, sizeof(char));
	if (!joined)
		return (NULL);
	seg = token->segments;
	while (seg)
	{
		ft_strlcat(joined, seg->text, total_len + 1);
		seg = seg->next;
	}
	return (joined);
}

void	add_segment_to_token(t_token *token, t_segment *seg)
{
	t_segment	*curr;

	curr = token->segments;
	if (!curr)
	{
		token->segments = seg;
		return ;
	}
	while (curr->next)
		curr = curr->next;
	curr->next = seg;
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

void	parse_and_create_token(t_data *data, char *input, int *start, int *end)
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
