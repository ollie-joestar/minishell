/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:49:14 by hanjkim           #+#    #+#             */
/*   Updated: 2024/11/19 15:28:57 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	set_token_type(t_token *token)
{
	if (token->word && !ft_strncmp(token->word, "<", 2))
		token->type = INPUT;
	else if (token->word && !ft_strncmp(token->word, "<<", 3))
		token->type = HEREDOC;
	else if (token->word && !ft_strncmp(token->word, ">", 2))
		token->type = REPLACE;
	else if (token->word && !ft_strncmp(token->word, ">>", 3))
		token->type = APPEND;
	else if (token->word && !ft_strncmp(token->word, "|", 2))
		token->type = PIPE;
}

void	process_token(t_data *data, t_token **token, int type)
{
	t_token *temp;

	temp = *token;
	if ((*token)->left)
		(*token)->left->right = (*token)->right;
	if ((*token)->right)
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
	t_token *token;

	if (!data->token)
		bruh(data, "No words to tokenize", 1);
	while (data->token && data->token->left)
		data->token = data->token->left;
	/*print_tokens(data->token);*/
	token = data->token;
	if (token)
	{
		/*ft_printf("Tokenizing\n");*/
		set_token_type(token);
		/*print_token(token);*/
		check_for_needed_expansion(data);
		if (token->type != WORD)
			process_token(data, &token, token->type);
		else
			token = token->right;
	}
}
