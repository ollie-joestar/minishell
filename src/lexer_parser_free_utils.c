/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser_free_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:15:16 by hanjkim           #+#    #+#             */
/*   Updated: 2025/03/05 16:17:47 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Free the segments of a token
void	free_token_segments(t_token *token)
{
	t_segment	*seg;
	t_segment	*next;

	if (!token->segments)
		return ;
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

// Free all tokens by rewinding the token list
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
			ft_free(&current->word);
		free_token_segments(current);
		free(current);
		current = next;
	}
	data->token = NULL;
}

// Free a single token's segments
void	free_segment(t_segment **seg)
{
	t_segment	*next;

	while (*seg)
	{
		next = (*seg)->next;
		if ((*seg)->text)
			ft_free(&(*seg)->text);
		free(*seg);
		*seg = next;
	}
}

// Annihilate old token
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

// Free a single token node
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
