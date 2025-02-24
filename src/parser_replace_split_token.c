/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_replace_split_token.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:01:54 by oohnivch          #+#    #+#             */
/*   Updated: 2025/02/24 18:52:39 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_tokens(t_data *data, t_token *o_token, t_token *n_token)
{
	t_token	*last_token;

	last_token = n_token;
	while (last_token->next != NULL)
		last_token = last_token->next;
	if (o_token->prev)
	{
		o_token->prev->next = n_token;
		n_token->prev = o_token->prev;
	}
	if (!o_token->prev)
	{
		data->token = n_token;
		n_token->prev = NULL;
	}
	if (o_token->next)
	{
		last_token->next = o_token->next;
		o_token->next->prev = last_token;
	}
	if (!o_token->next)
		last_token->next = NULL;
	free_old_token(o_token);
}
