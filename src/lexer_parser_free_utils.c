/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser_free_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:15:16 by hanjkim           #+#    #+#             */
/*   Updated: 2025/02/16 16:21:53 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_token_segments(t_token *token)
{
	t_segment	*seg;
	t_segment	*next;

	seg = token->segments;
	while (seg)
	{
		next = seg->next;
		ft_free(&seg->text);
		free(seg);
		seg = next;
	}
	token->segments = NULL;
}

void	free_tokens(t_data *data)
{
	t_token	*current;
	t_token	*next;

	if (!data->token)
		return ;
	while (data->token != NULL && data->token->prev != NULL)
		data->token = data->token->prev;
	current = data->token;
	while (current != NULL)
	{
		next = current->next;
		if (current->word != NULL)
			free(current->word);
		free(current);
		current = next;
	}
	data->token = NULL;
}

void	free_segment(t_segment **seg)
{
	t_segment	*next;

	while (*seg)
	{
		next = (*seg)->next;
		if ((*seg)->text)
			free((*seg)->text);
		free(*seg);
		*seg = next;
	}
}

void	free_old_token(t_token *token)
{
	if (!token)
		return ;
	if (token->segments)
		free_segment(&token->segments);
	if (token->word)
		ft_free(&token->word);
	free(token);
	token = NULL;
}

void	free_token_node(t_token **token)
{
	if (token == NULL || *token == NULL)
		return ;
	if ((*token)->prev)
		(*token)->prev->next = (*token)->next;
	if ((*token)->next)
		(*token)->next->prev = (*token)->prev;
	if ((*token)->word)
		ft_free(&(*token)->word);
	if ((*token)->segments)
		free_segment(&(*token)->segments);
	free(*token);
	*token = NULL;
}
