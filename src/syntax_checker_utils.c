/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:07:37 by hanjkim           #+#    #+#             */
/*   Updated: 2024/12/08 20:38:31 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirection(t_token *token)
{
	if (token->type == INPUT || token->type == REPLACE
		|| token->type == APPEND || token->type == HEREDOC)
		return (true);
	return (false);
}

bool	unexpected_token_with_join(t_data *data, t_token *token)
{
	char	*joined;

	joined = join_segments(token);
	unexpected_token(data, joined);
	ft_free(&joined);
	return (false);
}
