/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:49:14 by hanjkim           #+#    #+#             */
/*   Updated: 2025/02/02 19:06:44 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	finalize_tokens(t_token *token_list)
{
	t_token		*curr;
	t_segment	*seg;
	t_segment	*next;
	char		*joined;
	bool		set_nothing_type;

	curr = token_list;
	while (curr)
	{
		if (curr->segments)
		{
			joined = join_segments(curr);
			set_nothing_type = false;
			if (!joined || joined[0] == '\0')
			{
				seg = curr->segments;		
				while (seg)
				{
					if (seg->env_not_found)
					{
						set_nothing_type = true;
						break;
					}
					seg = seg->next;
				}
			}
			if (set_nothing_type)
			{
				ft_free(&joined);
				curr->word = ft_strdup("");
				curr->type = NOTHING;
			}
			else
				curr->word = joined;
			seg = curr_segments;
			while (seg)
			{
				next = seg->next;
				ft_free(&seg->text);
				free(seg);
				seg = next;
			}
			curr->segments = NULL;
		}
		curr = curr->next;
	}
}

char	*finalize_redirection_token(t_data *data, t_token *token)
{
	t_segment	*seg;
	char		*result;
	char		*temp;
	char		*expanded_segment;

	result = ft_calloc(1, 1);
	if (!result)
		return (NULL);
	seg = token->segments;
	while (seg)
	{
		if (seg->single_quoted)
			expanded_segment = ft_strdup(seg->text);
		else
			expanded_segment = expand(data, seg->text);
		if (!expanded_segment)
			return (ft_free(&result), NULL);
		temp = join2(result, expanded_segment);
		ft_free(&result);
		ft_free(&expanded_segment);
		result = temp;
		if (!result)
			return (NULL);
		seg = seg->next;
	}
	return (result);
}

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

void	process_redirection(t_data *data, t_token **token)
{
	t_token	*redirection_token;
	t_token	*filename_token;
	char	*final_filename;
	char	*original_filename;

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
	else if (redirection_token->type == INPUT
		|| redirection_token->type == REPLACE
		|| redirection_token->type == APPEND)
		filename_token->type = redirection_token->type;
	final_filename = finalize_redirection_token(data, filename_token);
	if (!final_filename || final_filename[0] == '\0')
	{
		original_filename = join_segments(filename_token);
		mspec2(original_filename, "ambiguous redirect\n");
		ft_free(&original_filename);
		data->status = 1;
		data->ambig_redir = 1;
		ft_free(&final_filename);
		return;
	}
	free_token_segments(filename_token);
	filename_token->word = final_filename;
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

char	*expand_segment(t_data *data, t_segment *seg, t_token *token)
{
	char	*expanded;

	(void)token;
	if (seg->single_quoted)
		return (ft_strdup(seg->text));
	expanded = expand(data, seg->text);
	if (!expanded)
		return (ft_strdup(""));
	if (!seg->single_quoted && !seg->double_quoted && seg->text[0] == '$' && expanded[0] == '\0')
        	seg->env_not_found = true;
	return (expanded);
}

void	expand_tokens(t_data *data)
{
	t_token		*current;
	char		*expanded;
	t_segment	*seg;

	data->ambig_redir = 0;
	current = data->token;
	while (current != NULL)
	{
		seg = current->segments;
		while (seg)
		{
			expanded = expand_segment(data, seg, current);
			if (!expanded)
				return ;
			ft_free(&seg->text);
			seg->text = expanded;
			seg = seg->next;
			if (current->type != WORD && current->type != PIPE)
			{
				process_redirection(data, &current);
				if (data->ambig_redir)
				{
					free_tokens(data);
					return ;
				}
			}
		}
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
	split_tokens(data);
	replace_tokens(data);
	while (data->token && data->token->prev != NULL)
		data->token = data->token->prev;
	finalize_tokens(data->token);
}
