/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:49:14 by hanjkim           #+#    #+#             */
/*   Updated: 2024/11/21 23:53:53 by hanjkim          ###   ########.fr       */
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
//Still needs a LOT of work
void split_quoted_token(t_data *data) {
    t_token *current = data->token;

    while (current) {
        char *start_quote = ft_strchr(current->word, SQ) ? ft_strchr(current->word, SQ) : ft_strchr(current->word, DQ);
        char *end_quote = start_quote ? ft_strchr(start_quote + 1, *start_quote) : NULL;

        if (start_quote && end_quote) {
            size_t prefix_len = start_quote - current->word;
            size_t quoted_len = end_quote - start_quote - 1;
            size_t suffix_len = ft_strlen(current->word) - (prefix_len + quoted_len + 2);

            char *prefix = prefix_len > 0 ? ft_substr(current->word, 0, prefix_len) : NULL;
            char *quoted = quoted_len > 0 ? ft_substr(current->word, prefix_len + 1, quoted_len) : NULL;
            char *suffix = suffix_len > 0 ? ft_substr(current->word, prefix_len + quoted_len + 2, suffix_len) : NULL;

            t_token *prefix_token = prefix ? ft_calloc(1, sizeof(t_token)) : NULL;
            t_token *quoted_token = quoted ? ft_calloc(1, sizeof(t_token)) : NULL;
            t_token *suffix_token = suffix ? ft_calloc(1, sizeof(t_token)) : NULL;

            if (prefix_token) {
                prefix_token->type = WORD;
                prefix_token->word = prefix;
            }
            if (quoted_token) {
                quoted_token->type = WORD;
                quoted_token->word = quoted;
            }
            if (suffix_token) {
                suffix_token->type = WORD;
                suffix_token->word = suffix;
            }
            if (prefix_token) {
                prefix_token->left = current->left;
                if (current->left) {
                    current->left->right = prefix_token;
                } else {
                    data->token = prefix_token;
                }
                prefix_token->right = quoted_token ? quoted_token : suffix_token;
            }
            if (quoted_token) {
                quoted_token->left = prefix_token;
                quoted_token->right = suffix_token;
            }
            if (suffix_token) {
                suffix_token->left = quoted_token ? quoted_token : prefix_token;
                suffix_token->right = current->right;
                if (current->right) {
                    current->right->left = suffix_token;
                }
            }
            if (!prefix_token) {
                if (quoted_token) {
                    quoted_token->left = current->left;
                    if (current->left) {
                        current->left->right = quoted_token;
                    } else {
                        data->token = quoted_token;
                    }
                } else if (suffix_token) {
                    suffix_token->left = current->left;
                    if (current->left) {
                        current->left->right = suffix_token;
                    } else {
                        data->token = suffix_token;
                    }
                }
            }
            ft_free(&current->word);
            free(current);
        }
        current = current ? current->right : NULL;
    }
}

void tokenization(t_data *data)
{
    t_token *token;

    if (!data->token)
        bruh(data, "No words to tokenize", 1);
    while (data->token && data->token->left)
        data->token = data->token->left;
    merge_quoted_tokens(data);
    print_tokens(data->token);
    split_quoted_token(data);
    print_tokens(data->token);
//    check_for_needed_expansion(data);
    token = data->token;
    while (token)
    {
        set_token_type(token);
        if (token->type != WORD && token->type != PIPE)
            process_redirection(data, &token);
        token = token->right;
    }
}
