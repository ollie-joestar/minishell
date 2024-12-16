/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:49:14 by hanjkim           #+#    #+#             */
/*   Updated: 2024/12/16 16:28:33 by oohnivch         ###   ########.fr       */
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
	char	*temp_word;
	char	*here_result;
	int		to_expand;

	redirection_token = *token;
	filename_token = redirection_token->next;
	if (!filename_token)
		bruh(data, "Expected filename after redirection", 2);
	filename_token->type = redirection_token->type;
	if (redirection_token->type == HEREDOC)
	{
		to_expand = (filename_token->segments->double_quoted ||
					filename_token->segments->single_quoted);
		temp_word = join_segments(filename_token);
		if (!temp_word)
			bruh(data, "Failed to join filename segments for HEREDOC", 2);
		here_result = here_doc(data, temp_word, to_expand);
		ft_free(&temp_word);
		free_token_node(&filename_token);
		filename_token = create_token_from_string(here_result);
		ft_free(&here_result);
		if (!filename_token)
			bruh(data, "Failed to create token from here_doc result", 2);
		filename_token->type = HEREDOC;
		filename_token->next = redirection_token->next;
	}
	filename_token->prev = redirection_token->prev;
	if (filename_token->next)
		filename_token->next->prev = filename_token;
	if (filename_token->prev)
		filename_token->prev->next = filename_token;
	free_old_token(redirection_token);
	*token = filename_token;
}

char	*expand_segment(t_data *data, t_segment *seg)
{
	if (seg->single_quoted)
		return (ft_strdup(seg->text));
	return (expand(data, seg->text));
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
			if (expanded)
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
