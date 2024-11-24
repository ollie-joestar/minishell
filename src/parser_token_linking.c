/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token_linking.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:43:52 by hanjkim           #+#    #+#             */
/*   Updated: 2024/11/24 23:47:08 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void insert_token(t_token *new_token, t_token *start_token, t_token *end_token)
{
	if (start_token->left) 
	{
		start_token->left->right = new_token;
		new_token->left = start_token->left;
	} else
		new_token->left = NULL;
	if (end_token->right)
	{
		end_token->right->left = new_token;
		new_token->right = end_token->right;
	} else
		new_token->right = NULL;
}
