/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_set_token_types.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:48:26 by hanjkim           #+#    #+#             */
/*   Updated: 2025/03/03 16:39:48 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Check if the token has an unquoted operator
bool	has_unquoted_operator(t_token *token)
{
	t_segment	*seg;

	seg = token->segments;
	while (seg)
	{
		if (!seg->single_quoted && !seg->double_quoted)
		{
			if (!ft_strncmp(seg->text, "<", 2)
				|| !ft_strncmp(seg->text, "<<", 3)
				|| !ft_strncmp(seg->text, ">", 2)
				|| !ft_strncmp(seg->text, ">>", 3)
				|| !ft_strncmp(seg->text, "|", 2))
				return (true);
		}
		seg = seg->next;
	}
	return (false);
}

// Assign type based on reconstructed segment string
void	assign_token_type_from_joined(t_token *token, char *joined)
{
	if (!ft_strncmp(joined, "<", 2))
		token->type = INPUT;
	else if (!ft_strncmp(joined, "<<", 3))
		token->type = HEREDOC;
	else if (!ft_strncmp(joined, ">", 2))
		token->type = REPLACE;
	else if (!ft_strncmp(joined, ">>", 3))
		token->type = APPEND;
	else if (!ft_strncmp(joined, "|", 2))
		token->type = PIPE;
}

// literally just check if nothing token is nothing
void	set_nothing_type(t_token *token, char *joined)
{
	ft_free(&joined);
	token->word = ft_strdup("");
	if (!token->word)
		return ;
	token->type = NOTHING;
}

// Reconstruct copy of string and check type to be assigned
void	set_token_type(t_token *token_list)
{
	t_token	*current;
	char	*joined;
	bool	operator_unquoted;

	current = token_list;
	while (current != NULL)
	{
		joined = join_segments(current);
		if (!joined)
			return ;
		if (joined)
		{
			operator_unquoted = has_unquoted_operator(current);
			if (operator_unquoted)
				assign_token_type_from_joined(current, joined);
			else
				current->type = WORD;
			ft_free(&joined);
		}
		current = current->next;
	}
}
