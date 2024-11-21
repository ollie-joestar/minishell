/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:28:15 by hanjkim           #+#    #+#             */
/*   Updated: 2024/11/21 23:04:55 by hanjkim          ###   ########.fr       */
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

/*void check_for_needed_expansion(t_data *data)*/
/*{*/
/*    t_token *current;*/
/*    t_token *next;*/
/*    t_token *expanded_tokens;*/
/**/
/*    ft_printf("entered check_for_needed_expansion\n");*/
/*    current = data->token;*/
/*    while (current)*/
/*    {*/
/*        next = current->right;*/
/*        ft_printf("current->word = %s\n", current->word);*/
/*        if (requires_expansion(current->word))*/
/*        {*/
/*            print_tokens(data->token);*/
/*            expanded_tokens = expand_token(data, current->word);*/
/*            if (!expanded_tokens)*/
/*                bruh(data, "Failed to expand token", 1);*/
/*            insert_token(get_first_token(expanded_tokens), get_last_token(expanded_tokens), current);*/
/*            next = get_last_token(expanded_tokens)->right;*/
/*            free_old_token(current);*/
/*        }*/
/*        current = next;*/
/*    }*/
/*}*/

/*void check_for_needed_expansion(t_data *data)*/
/*{*/
/*    t_token *current = data->token;*/
/**/
/*    while (current)*/
/*    {*/
/*        t_token *next = current->right;*/
/**/
/*        if (current->word && requires_expansion(current->word))*/
/*        {*/
/*            join_and_trim_quotes(data);*/
/*            t_token *expanded_tokens = expand_token(data, current->word);*/
/*            if (!expanded_tokens)*/
/*                bruh(data, "Failed to expand token", 1);*/
/*            insert_token(get_first_token(expanded_tokens), get_last_token(expanded_tokens), current);*/
/*            free_old_token(current);*/
/*            next = get_last_token(expanded_tokens)->right;*/
/*        }*/
/*        current = next;*/
/*    }*/
/*}*/

char **ft_split_quotes(char *str)
{
    char **result;
    int i = 0, j = 0, k = 0;
    char quote = 0;

    result = ft_calloc(ft_strlen(str) + 1, sizeof(char *));
    if (!result)
        return NULL;

    while (str[i])
    {
        if ((str[i] == SQ || str[i] == DQ) && quote == 0)
            quote = str[i];
        else if (str[i] == quote)
            quote = 0;
        else if (str[i] == ' ' && quote == 0)
        {
            if (i > j)
            {
                result[k++] = ft_substr(str, j, i - j);
                if (!result[k - 1])
                {
                    free_arr(&result);
                    return NULL;
                }
            }
            j = i + 1;
        }
        i++;
    }
    if (i > j)
    {
        result[k++] = ft_substr(str, j, i - j);
        if (!result[k - 1])
        {
            free_arr(&result);
            return NULL;
        }
    }
    result[k] = NULL;

    return result;
}

char *ft_strjoin_free(char *s1, char *s2)
{
    char *joined_str;

    if (!s1 || !s2)
    {
        ft_free(&s1);
        return NULL;
    }

    joined_str = ft_strjoin(s1, s2);
    if (!joined_str)
    {
        ft_free(&s1);
        return NULL;
    }

    ft_free(&s1);
    return joined_str;
}

//this works for now
void merge_quoted_tokens(t_data *data) {
    t_token *current = data->token;
    t_token *start = NULL;
    t_token *end = NULL;
    char *joined_word = NULL;
    int inside_quotes = 0;

    while (current) {
        if (!inside_quotes && (current->type == WORD) && (ft_strchr(current->word, SQ) || ft_strchr(current->word, DQ))) {
            inside_quotes = 1;
            start = current;
            joined_word = ft_strdup(current->word);
        } else if (inside_quotes) {
            char *temp = ft_strjoin(joined_word, " ");
            ft_free(&joined_word);
            joined_word = ft_strjoin(temp, current->word);
            ft_free(&temp);
            if (ft_strchr(current->word, SQ) || ft_strchr(current->word, DQ)) {
                inside_quotes = 0;
                end = current;
            }
        }
        current = current->right;
        if (!inside_quotes && start && end) {
            t_token *new_token = ft_calloc(1, sizeof(t_token));
            new_token->type = WORD;
            new_token->word = joined_word;
            if (start->left)
                start->left->right = new_token;
            new_token->left = start->left;
            if (end->right)
                end->right->left = new_token;
            new_token->right = end->right;
            t_token *tmp = start;
            while (tmp != end->right) {
                t_token *next = tmp->right;
                ft_free(&tmp->word);
                free(tmp);
                tmp = next;
            }
            current = new_token->right;
            start = NULL;
            end = NULL;
            joined_word = NULL;
        }
    }
} 
