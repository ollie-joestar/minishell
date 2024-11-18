/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:16:31 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/18 16:17:33 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_slice(t_token *first, t_token *last)
{
	t_token *tmp;

	while (first != last)
	{
		tmp = first;
		first = first->right;
		free_token_node(&tmp);
	}
	free_token_node(&last);
}

t_token *get_first_token(t_token *token)
{
	while (token->left)
		token = token->left;
	return (token);
}

t_token *get_last_token(t_token *token)
{
	while (token->right)
		token = token->right;
	return (token);
}
