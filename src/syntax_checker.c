/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:06:16 by hanjkim           #+#    #+#             */
/*   Updated: 2025/03/03 16:42:46 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Check if there is a pipe in front of the token
bool	pipe_in_front(t_token *token)
{
	if (token && token->type == PIPE)
		return (true);
	return (false);
}

// Check if there is a double pipe
bool	double_pipe(t_token *token)
{
	if (token == NULL)
		return (false);
	if (token->type == PIPE)
	{
		if (token->next != NULL && token->next->type == PIPE)
			return (true);
		if (token->next == NULL)
			return (true);
	}
	return (false);
}

// Check if the token is a redirection without a filename
bool	missing_filename(t_token *token)
{
	if (token == NULL)
		return (false);
	if (is_redirection(token))
	{
		if (token->next == NULL)
			return (true);
		if (token->next->type != WORD)
			return (true);
	}
	return (false);
}

// Prints an error message for unexpected token in the line
void	unexpected_token(t_data *data, char *str)
{
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	if (str == NULL || str[0] == '\0')
		ft_putstr_fd("newline", STDERR_FILENO);
	else
		ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	data->status = STDERR_FILENO;
}

// Check if the syntax is valid for several cases
bool	valid_syntax(t_data *data, t_token *token)
{
	if (pipe_in_front(token))
		return (unexpected_token_with_join(data, token));
	while (token != NULL)
	{
		if (double_pipe(token))
		{
			if (token->next != NULL)
				return (unexpected_token_with_join(data, token->next));
			else
				return (unexpected_token_with_join(data, token));
		}
		if (missing_filename(token))
		{
			if (token->next != NULL)
				return (unexpected_token_with_join(data, token->next));
			else
				return (unexpected_token_with_join(data, token));
		}
		token = token->next;
	}
	return (true);
}
