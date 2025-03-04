/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:49:14 by hanjkim           #+#    #+#             */
/*   Updated: 2025/03/03 16:40:28 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Check if the token should be marked as NOTHING
bool	should_mark_nothing(t_token *token, char *joined)
{
	t_segment	*seg;
	bool		has_unquoted_missing;
	bool		has_quoted;

	seg = token->segments;
	has_unquoted_missing = false;
	has_quoted = false;
	if (!joined || joined[0] == '\0')
	{
		while (seg)
		{
			if (!seg->single_quoted && !seg->double_quoted
				&& seg->env_not_found)
				has_unquoted_missing = true;
			if (seg->single_quoted || seg->double_quoted)
				has_quoted = true;
			seg = seg->next;
		}
	}
	return (has_unquoted_missing && !has_quoted);
}

// Final step of tokenization to send to execution
void	finalize_token(t_token *token)
{
	t_segment	*tmp;
	char		*joined;
	bool		mark;

	if (!token->segments)
		return ;
	joined = join_segments(token);
	if (!joined)
		return ;
	mark = should_mark_nothing(token, joined);
	if (mark)
	{
		set_nothing_type(token, joined);
		return ;
	}
	else
		token->word = joined;
	while (token->segments)
	{
		tmp = token->segments;
		token->segments = token->segments->next;
		(ft_free(&tmp->text), free(tmp));
	}
}

// Cycle through all tokens and finalize them
void	finalize_tokens(t_token *token_list)
{
	t_token	*curr;

	curr = token_list;
	while (curr)
	{
		finalize_token(curr);
		curr = curr->next;
	}
}

/*// Finalize filename token in case of redirection*/
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
		if (!temp)
			return (ft_free(&result), ft_free(&expanded_segment), NULL);
		(ft_free(&result), ft_free(&expanded_segment));
		result = temp;
		seg = seg->next;
	}
	return (result);
}

// Main parser function
void	process_tokens(t_data *data)
{
	if (!data->token)
		return ;
	expand_tokens(data);
	split_tokens(data);
	finalize_tokens(data->token);
}
