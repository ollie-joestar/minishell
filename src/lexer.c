/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:49:14 by hanjkim           #+#    #+#             */
/*   Updated: 2024/11/19 17:00:28 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void set_token_type(t_token *token)
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

/*void	process_token(t_data *data, t_token **token, int type)*/
/*{*/
/*	t_token *temp;*/
/*	char *temp_word;*/
/**/
/*	temp = *token;*/
/*	if ((*token)->left)*/
/*		(*token)->left->right = (*token)->right;*/
/*	if ((*token)->right)*/
/*		(*token)->right->left = (*token)->left;*/
/*	*token = (*token)->right;*/
/*	(*token)->type = type;*/
/*	if (type == HEREDOC)*/
/*	{*/
/*		temp_word = (*token)->word;*/
/*		(*token)->word = here_doc(data, (*token)->word);*/
/*		ft_free(&temp_word);*/
/*	}*/
/*	free_token_node(&temp);*/
/*}*/

void process_redirection(t_data *data, t_token **token)
{
    t_token *redirection_token;
    t_token *filename_token;
	char *temp_word;

	redirection_token = *token;
	filename_token = redirection_token->right;
    if (!filename_token)
        bruh(data, "Expected filename after redirection", 1);
    filename_token->type = redirection_token->type;
    if (redirection_token->left)
        redirection_token->left->right = filename_token;
    filename_token->left = redirection_token->left;
	*token = filename_token;
	if (filename_token->type == HEREDOC)
	{
		temp_word = filename_token->word;
		filename_token->word = here_doc(data, filename_token->word);
		ft_free(&temp_word);
	}
	free_token_node(&redirection_token);
}

void tokenization(t_data *data)
{
    t_token *token;

    if (!data->token)
        bruh(data, "No words to tokenize", 1);
    while (data->token && data->token->left)
        data->token = data->token->left;
    token = data->token;
    while (token)
    {
        set_token_type(token);
        if (token->type != WORD && token->type != PIPE)
            process_redirection(data, &token);
        token = token->right;
    }
}
