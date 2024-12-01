/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_replace_split_token.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 20:20:47 by hanjkim           #+#    #+#             */
/*   Updated: 2024/12/01 22:40:24 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_replace(t_data *data, t_token *original, t_token *new_head)
{
	t_replace	*new;
	t_replace	*last;

	new = (t_replace *)ft_calloc(1, sizeof(t_replace));
	if (!new)
		bruh(data, "Failed to allocate memory for token replacement", 1);
	new->original = original;
	new->new_head = new_head;
	new->next = NULL;
	if (!data->replacements)
		data->replacements = new;
	else
	{
		last = data->replacements;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

void	replace_token(t_data *data, t_token *original, t_token *new_head)
{
	t_token	*new_tail;

	new_tail = new_head;
	while (new_tail->next != NULL)
		new_tail = new_tail->next;
	if (original->prev)
	{
		original->prev->next = new_head;
		new_head->prev = original->prev;
	}
	else
	{
		data->token = new_head;
		new_head->prev = NULL;
	}
	if (original->next)
	{
		new_tail->next = original->next;
		original->next->prev = new_tail;
	}
	else
		new_tail->next = NULL;
	free_old_token(original);
}

void	replace_tokens(t_data *data)
{
	t_replace	*curr_replace;
	t_replace	*next_replace;

	curr_replace = data->replacements;
	while (curr_replace != NULL)
	{
		next_replace = curr_replace->next;
		replace_token(data, curr_replace->original, curr_replace->new_head);
		free(curr_replace);
		curr_replace = next_replace;
	}
	data->replacements = NULL;
}
