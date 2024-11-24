/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:49:14 by hanjkim           #+#    #+#             */
/*   Updated: 2024/11/24 23:46:23 by hanjkim          ###   ########.fr       */
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

void expand_tokens(t_data *data) {
    t_token *token = data->token;

    while (token) {
        print_token(token);
        expand_token(data, token);
        set_token_type(token);
        if (token->type != WORD && token->type != PIPE)
            process_redirection(data, &token);
        token = token->right;
    }
}

//maybe i'll need this later
/*void join_tokens(t_data *data)*/
/*{*/
/*    t_token *token;*/
/*    size_t total_len = 0;*/
/*    size_t token_count = 0;*/
/*    char *result;*/
/*    char *ptr;*/
/*    size_t len;*/
/**/
/*    token = data->token;*/
/*    while (token && token->left)*/
/*        token = token->left;*/
/*    data->token = token;*/
/*    token = data->token;*/
/*    while (token)*/
/*    {*/
/*        total_len += ft_strlen(token->word);*/
/*        token_count++;*/
/*        token = token->right;*/
/*    }*/
/*    if (token_count > 1)*/
/*        total_len += (token_count - 1);*/
/*    result = ft_calloc(total_len + 1, sizeof(char));*/
/*    if (!result)*/
/*        return (bruh(data, "Failed to allocate memory for joined tokens", 1));*/
/*    token = data->token;*/
/*    ptr = result;*/
/*    while (token)*/
/*    {*/
/*        len = ft_strlen(token->word);*/
/*        ft_memcpy(ptr, token->word, len);*/
/*        ptr += len;*/
/*        if (token->right)*/
/*            *ptr = ' ', ptr++;*/
/*        token = token->right;*/
/*    }*/
/*    data->joined_line = result;*/
/*}*/

void tokenization(t_data *data)
{
    t_token *token;

    if (!data->token)
        bruh(data, "No words to tokenize", 1);
    while (data->token && data->token->left)
        data->token = data->token->left;
    merge_quoted_tokens(data);
    /*print_tokens(data->token);*/
    split_quoted_token(data);
    /*print_tokens(data->token);*/
    token = data->token;
    expand_tokens(data);
}
