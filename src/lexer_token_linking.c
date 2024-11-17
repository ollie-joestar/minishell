/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_linking.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:43:52 by hanjkim           #+#    #+#             */
/*   Updated: 2024/11/17 17:44:11 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	insert_token(t_lex_token *fntok, t_lex_token *lntok, t_lex_token *old_token)
{
	if (old_token->left)
		old_token->left->right = fntok;
	fntok->left = old_token->left;

	if (old_token->right)
		old_token->right->left = lntok;
	lntok->right = old_token->right;
}

void	update_token_links(t_lex_token *first_new_token, t_lex_token *last_new_token, t_lex_token *old_token)
{
	if (old_token->left)
		old_token->left->right = first_new_token;
	first_new_token->left = old_token->left;

	if (old_token->right)
		old_token->right->left = last_new_token;
	last_new_token->right = old_token->right;
}
