/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_replace_split_token.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 20:20:47 by hanjkim           #+#    #+#             */
/*   Updated: 2025/02/23 18:55:28 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void replace_tokens(t_data *data, t_token *old_token, t_token *new_token)
{
 t_token *last_token;

    last_token = new_token;
    while (last_token->next != NULL)
        last_token = last_token->next;
    if (old_token->prev) 
	{
        old_token->prev->next = new_token;
        new_token->prev = old_token->prev;
    }
    if (!old_token->prev) 
	{
        data->token = new_token;
        new_token->prev = NULL;
    }
    if (old_token->next) 
	{
        last_token->next = old_token->next;
        old_token->next->prev = last_token;
    }
    if (!old_token->next)
        last_token->next = NULL;
    free_old_token(old_token);
}
