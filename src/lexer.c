/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:49:14 by hanjkim           #+#    #+#             */
/*   Updated: 2024/11/17 17:38:19 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	check_token_type(t_lex_token *token)
{

	if (*token->word && ft_strncmp(token->word, "<", 2))
		token->type = INPUT;
	else if (*token->word && ft_strncmp(token->word, "<<", 3))
		token->type = HEREDOC;
	else if (*token->word && ft_strncmp(token->word, ">", 2))
		token->type = REPLACE;
	else if (*token->word && ft_strncmp(token->word, ">>", 3))
		token->type = APPEND;
	else if (*token->word && ft_strncmp(token->word, "|", 2))
		token->type = PIPE;
}

void	process_token(t_data *data, t_lex_token **token, int type)
{
	t_lex_token *temp;

	temp = *token;
	(*token)->left->right = (*token)->right;
	(*token)->right->left = (*token)->left;
	*token = (*token)->right;
	(*token)->type = type;
	if (type == HEREDOC)
	{
		char *temp_word = (*token)->word;
		(*token)->word = here_doc(data, (*token)->word);
		ft_free(&temp_word);
	}
	free_token_node(&temp);
}

void	tokenization(t_data *data)
{
	t_lex_token *token;

	while (data->token && data->token->left)
		data->token = data->token->left;
	check_for_needed_expansion(data);
	token = data->token;
	while (token)
	{
		check_token_type(token);
		if (token->type == INPUT || token->type == REPLACE || 
			token->type == APPEND || token->type == PIPE || 
			token->type == HEREDOC)
			process_token(data, &token, token->type);
		else
			token = token->right;
	}
}
