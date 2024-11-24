/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_merge_quoted_tokens.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:49:19 by hanjkim           #+#    #+#             */
/*   Updated: 2024/11/24 19:39:59 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void find_word_in_quotes(t_token *current, t_merge *merge_state)
{
    char *single_quote_ptr;
    char *double_quote_ptr;
    char *start_ptr;
    char *closing_quote_ptr;

    single_quote_ptr = ft_strchr(current->word, SQ);
    double_quote_ptr = ft_strchr(current->word, DQ);
    if (single_quote_ptr && (!double_quote_ptr || single_quote_ptr  
        < double_quote_ptr)) {
        merge_state->quote_char = SQ;
        start_ptr = single_quote_ptr;
    } else if (double_quote_ptr) {
        merge_state->quote_char = DQ;
        start_ptr = double_quote_ptr;
    } else
        return;
    merge_state->is_inside_quotes = 1;
    merge_state->start_token = current;
    merge_state->combined_word = ft_strdup(current->word);
    closing_quote_ptr = ft_strchr(start_ptr + 1, merge_state->quote_char);
    if (closing_quote_ptr) {
        merge_state->is_inside_quotes = 0;
        merge_state->end_token = current;
    }
}

void append_quoted_token(t_token *current, t_merge *merge_state)
{
    char *word;
    char *ptr;
    int quote_count;

    quote_count = 0;
    word = current->word;
    merge_state->combined_word = ft_strjoin_and_free(merge_state->combined_word, ft_strdup(" "));
    merge_state->combined_word = ft_strjoin_and_free(merge_state->combined_word, ft_strdup(word));
    ptr = merge_state->combined_word;
    while ((ptr = ft_strchr(ptr, merge_state->quote_char)) != NULL) {
        quote_count++;
        ptr++;
    }
    if (quote_count % 2 == 0) {
        merge_state->is_inside_quotes = 0;
        merge_state->end_token = current;
    } else
        merge_state->is_inside_quotes = 1;
}

void create_merge(t_data *data, t_merge *merge_state, t_token **current)
{
    t_token *new_token;
    t_token *tmp;
    t_token *next;

    new_token = create_token();
    new_token->type = WORD;
    new_token->word = merge_state->combined_word;
    insert_token(new_token, merge_state->start_token, merge_state->end_token);
    if (merge_state->start_token == data->token)
        data->token = new_token;
    *current = new_token->right;
    tmp = merge_state->start_token;
    while (tmp != merge_state->end_token->right) {
        next = tmp->right;
        free_token_node(&tmp);
        tmp = next;
    }
}

void merge_quoted_tokens(t_data *data)
{
    t_merge merge_state;
    t_token *current;

    ft_memset(&merge_state, 0, sizeof(t_merge));
    current = data->token;
    while (current) {
        if (!merge_state.is_inside_quotes)
            find_word_in_quotes(current, &merge_state);
        else
            append_quoted_token(current, &merge_state);
        current = current->right;
        if (!merge_state.is_inside_quotes && merge_state.start_token \
            && merge_state.end_token) {
            create_merge(data, &merge_state, &current);
            ft_memset(&merge_state, 0, sizeof(t_merge));
        }
    }
}
