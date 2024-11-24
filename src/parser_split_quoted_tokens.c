/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split_quoted_tokens.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 19:45:02 by hanjkim           #+#    #+#             */
/*   Updated: 2024/11/24 23:07:40 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    find_quotes_in_word(char *word, char **start_quote, char **end_quote)
{
    *start_quote = ft_strchr(word, SQ);
    if (!*start_quote)
        *start_quote = ft_strchr(word, DQ);
    *end_quote = NULL;
    if (*start_quote)
        *end_quote = ft_strchr((*start_quote) + 1, **start_quote);
}



void    replace_curr_token(t_data *data, t_token *current, t_split *tokens) 
{
    t_token *left;
    t_token *right;
    t_token *first_new;
    t_token *last_new;
    
    left = current->left;
    right = current->right;
    first_new = get_first_split_token(tokens);
    last_new = get_last_split_token(tokens);
    if (tokens->prefix)
        adjust_prefix_links(tokens->prefix, left, right, tokens);
    if (tokens->quoted)
        adjust_quoted_links(tokens->quoted, left, right, tokens);
    if (tokens->suffix)
        adjust_suffix_links(tokens->suffix, left, right, tokens);
    update_data_token(data, left, first_new);
    if (right && last_new)
        right->left = last_new;
    ft_free(&current->word);
    free(current);
}
//Could be leaking?
void initialize_tokens(t_split *tokens)
{
    if (tokens->prefix_str)
    {
        tokens->prefix = create_token();
        tokens->prefix->type = WORD;
        tokens->prefix->word = tokens->prefix_str;
    }
    if (tokens->quoted_str)
    {
        tokens->quoted = create_token();
        tokens->quoted->type = WORD;
        tokens->quoted->word = tokens->quoted_str;
    }
    if (tokens->suffix_str)
    {
        tokens->suffix = create_token();
        tokens->suffix->type = WORD;
        tokens->suffix->word = tokens->suffix_str;
    }
}

void slice_substrings(t_token *current, t_split *tokens) 
{
    tokens->prefix_len = tokens->start_quote - current->word;
    tokens->quoted_len = tokens->end_quote - tokens->start_quote - 1;
    tokens->suffix_len = ft_strlen(current->word) - 
                         (tokens->prefix_len + tokens->quoted_len + 2);
    tokens->prefix_str = slice(current->word, 0, tokens->prefix_len);
    tokens->quoted_str = slice(current->word, tokens->prefix_len + 1,
                               tokens->quoted_len);
    tokens->suffix_str = slice(current->word, tokens->prefix_len +
                               tokens->quoted_len + 2, tokens->suffix_len);
}

void split_quoted_token(t_data *data)
{
    t_token *current;
    t_split tokens;

    current = data->token;
    while (current) {
        memset(&tokens, 0, sizeof(t_split));
        find_quotes_in_word(current->word, &tokens.start_quote, 
                            &tokens.end_quote);
        if (tokens.start_quote && tokens.end_quote)
        {
            slice_substrings(current, &tokens);
            initialize_tokens(&tokens);
            replace_curr_token(data, current, &tokens);
            current = update_pointer(&tokens);
        } 
        else
            current = current->right;
    }
}
