/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:49:14 by hanjkim           #+#    #+#             */
/*   Updated: 2024/12/16 21:31:01 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	finalize_tokens(t_token *token_list)
{
	t_token		*curr;
	t_segment	*seg;
	t_segment	*next;
	char		*joined;

	curr = token_list;
	while (curr)
	{
		if (curr->segments)
		{
			joined = join_segments(curr);
			seg = curr->segments;
			while (seg)
			{
				next = seg->next;
				ft_free(&seg->text);
				free(seg);
				seg = next;
			}
			curr->segments = NULL;
			curr->word = joined;
		}
		curr = curr->next;
	}
}

void	process_redirection(t_data *data, t_token **token)
{
	t_token	*redirection_token;
	t_token	*filename_token;

	redirection_token = *token;
	filename_token = redirection_token->next;
	if (!filename_token)
	{
		unexpected_token(data, NULL);
		return ;
	}
	filename_token->type = WORD;
	if (redirection_token->type == HEREDOC)
	{
		filename_token = handle_heredoc(data, redirection_token,
				filename_token);
		if (!filename_token)
			return ;
	}
	filename_token->prev = redirection_token->prev;
	if (filename_token->next)
		filename_token->next->prev = filename_token;
	if (filename_token->prev)
		filename_token->prev->next = filename_token;
	else
		data->token = filename_token;
	free_old_token(redirection_token);
	*token = filename_token;
}

char	*expand_segment(t_data *data, t_segment *seg)
{
	char	*expanded;

	if (seg->single_quoted)
		return (ft_strdup(seg->text));
	expanded = expand(data, seg->text);
	if (!expanded)
	{
		expanded = ft_strdup("");
		if (!expanded)
			return (NULL);
	}
	return (expanded);
}

void	expand_tokens(t_data *data)
{
	t_token		*current;
	char		*expanded;
	t_segment	*seg;

	current = data->token;
	while (current != NULL)
	{
		seg = current->segments;
		while (seg)
		{
			expanded = expand_segment(data, seg);
			if (!expanded)
				return ;
			else
			{
				ft_free(&seg->text);
				seg->text = expanded;
			}
			seg = seg->next;
		}
		if (current->type != WORD && current->type != PIPE)
			process_redirection(data, &current);
		current = current->next;
	}
}

void	process_tokens(t_data *data)
{
	if (!data->token)
		bruh(data, "No tokens available for processing", 2);
	while (data->token && data->token->prev != NULL)
		data->token = data->token->prev;
	expand_tokens(data);
	while (data->token && data->token->prev != NULL)
		data->token = data->token->prev;
	finalize_tokens(data->token);
}
