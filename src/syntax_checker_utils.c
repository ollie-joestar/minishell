/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:07:37 by hanjkim           #+#    #+#             */
/*   Updated: 2025/02/27 19:12:53 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checks if the token is a redirection
bool	is_redirection(t_token *token)
{
	if (token->type == INPUT || token->type == REPLACE
		|| token->type == APPEND || token->type == HEREDOC)
		return (true);
	return (false);
}

// Joins all segments of a token into a single string
// and sets up the tokens for syntax error messages
bool	unexpected_token_with_join(t_data *data, t_token *token)
{
	char	*joined;
	char	*err_token;

	joined = join_segments(token);
	err_token = NULL;
	if (token->next == NULL)
	{
		if (token->type == PIPE)
			err_token = "|";
		else if (is_redirection(token))
		{
			if (token->prev != NULL && is_redirection(token->prev))
				if (joined && joined[0] != '\0')
					err_token = joined;
		}
	}
	else
		if (joined && joined[0] != '\0')
			err_token = joined;
	unexpected_token(data, err_token);
	ft_free(&joined);
	return (false);
}
