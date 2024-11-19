/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:28:15 by hanjkim           #+#    #+#             */
/*   Updated: 2024/11/19 23:41:27 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int requires_expansion(char *word)
{
    int has_dollar;
    int single_quote_count;
    int double_quote_count;
    int i;

    has_dollar = 0;
    single_quote_count = 0;
    double_quote_count = 0;
    i = 0;
    if (ft_strchr(word, DOLLAR) != NULL)
        has_dollar = 1;
    while (word[i])
    {
        if (word[i] == SQ)
            single_quote_count++;
        else if (word[i] == DQ)
            double_quote_count++;
        i++;
    }
    if (has_dollar)
        return (1);
    if (single_quote_count % 2 != 0)
        return (1);
    if (double_quote_count % 2 != 0)
        return (1);
    return (0);
}

char	**expand_token_to_words(t_data *data, char *word)
{
	char	*expanded_word;
	char	**tokens;

	//bruh(data, "Failed to expand token words", 1);
	expanded_word = process_word_expansion(data, word);
	if (!expanded_word)
		bruh(data, "Failed to expand line", 1);
	tokens = ft_split(expanded_word, ' ');
	if (!tokens)
		bruh(data, "Failed to split expanded line", 1);
	return (tokens);
}

t_token *init_expanded_tokens(t_data *data, char **expanded_words)
{
    int     i;
    t_token *new_token;
    t_token *temp;
    t_token *head;

    i = -1;
    new_token = NULL;
    head = NULL;
    ft_printf("entered init_expanded_tokens\n");
    while (expanded_words[++i])
    {
        temp = create_token();
        ft_printf("expanded_words[%d] = %s\n", i, expanded_words[i]);
        if (!temp)
            bruh(data, "Failed to create expanded token", 1);
        temp->word = ft_strdup(expanded_words[i]);
        if (!temp->word)
            bruh(data, "Failed to duplicate expanded token word", 1);
        if (!head)
            head = temp;
        else
        {
            new_token->right = temp;
            temp->left = new_token;
        }
        new_token = temp;
    }
    ft_printf("exiting init_expanded_tokens\n");
    return (head);
}

t_token *expand_token(t_data *data, char *word)
{
    char    **expanded_words;
    t_token *new_tokens;

    ft_printf("entered expand_token\n");
    expanded_words = expand_token_to_words(data, word);
    if (!expanded_words)
        bruh(data, "Failed to expand token", 1);
    new_tokens = init_expanded_tokens(data, expanded_words);
    if (!new_tokens)
    {
        free_arr(&expanded_words);
        bruh(data, "Failed to create expanded tokens", 1);
    }
    free_arr(&expanded_words);
    return new_tokens;
}

void insert_new_token_into_list(t_token *expanded_tokens, t_token *old_token)
{
    t_token *last_new_token;

    last_new_token = expanded_tokens;
    while (last_new_token->right)
        last_new_token = last_new_token->right;
    update_token_links(expanded_tokens, last_new_token, old_token);
    free_old_token(old_token);
}
/*
void check_for_needed_expansion(t_data *data)
{
    t_token *current;
    t_token *next;
    t_token *expanded_tokens;

    ft_printf("entered check_for_needed_expansion\n");
    current = data->token;
    ft_printf("current->word = %s\n", current->word);
    while (current)
    {
        next = current->right;
        if (requires_expansion(current->word))
        {
            expanded_tokens = expand_token(data, current->word);
            if (!expanded_tokens)
                bruh(data, "Failed to expand token", 1);
            insert_token(get_first_token(expanded_tokens), get_last_token(expanded_tokens), current);
            next = expanded_tokens;
            while (next && next->right)
                next = next->right;
            next = next->right;
        }
        current = next;
    }
}*/

void check_for_needed_expansion(t_data *data)
{
    t_token *current;
    t_token *next;
    t_token *expanded_tokens;

    ft_printf("entered check_for_needed_expansion\n");
    current = data->token;
    while (current)
    {
        next = current->right;
        ft_printf("current->word = %s\n", current->word);
        if (requires_expansion(current->word))
        {
            expanded_tokens = expand_token(data, current->word);
            if (!expanded_tokens)
                bruh(data, "Failed to expand token", 1);
            insert_token(get_first_token(expanded_tokens), get_last_token(expanded_tokens), current);
            next = get_last_token(expanded_tokens)->right;
        }
        current = next;
    }
}

