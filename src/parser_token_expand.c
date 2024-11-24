/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:28:15 by hanjkim           #+#    #+#             */
/*   Updated: 2024/11/24 23:33:18 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_strjoin_char_free(char *s1, char c) 
{
    size_t len1;
    char *new_str;

    len1 = ft_strlen(s1);
    new_str = ft_calloc(len1 + 2, sizeof(char));
    if (!new_str) {
        ft_free(&s1);
        return (NULL);
    }
    if (s1)
        new_str = ft_strdup(s1);
    new_str[len1] = c;
    ft_free(&s1);
    return (new_str);
}

void expand_token(t_data *data, t_token *token)
{
    char *word = token->word;
    char *new_word = NULL;
    size_t i = 0;
    size_t len = ft_strlen(word);
    int in_single_quote = 0;
    int in_double_quote = 0;
    size_t var_start;
    size_t var_len;
    char *var_name;
    char *var_value;

    word = token->word;
    new_word = ft_strdup("");
    i = 0;
    len = ft_strlen(word);
    in_single_quote = 0;
    in_double_quote = 0;
    while (i < len) {
        if (word[i] == '\'' && !in_double_quote) 
        {
            in_single_quote = !in_single_quote;
            i++;
            continue;
        } 
        else if (word[i] == '\"' && !in_single_quote) 
        {
            in_double_quote = !in_double_quote;
            i++;
            continue;
        } 
        else if (word[i] == '$' && !in_single_quote) 
        {
            var_start = i + 1;
            var_len = 0;
            if (word[var_start] == '\0' || word[var_start] == ' ' || word[var_start] == '$' || word[var_start] == '\"' || word[var_start] == '\'') 
            {
                new_word = ft_strjoin_char_free(new_word, '$');
                i++;
                continue;
            }
            while (word[var_start + var_len] && (ft_isalnum(word[var_start + var_len]) || word[var_start + var_len] == '_'))
                var_len++;
            var_name = ft_substr(word, var_start, var_len);
            var_value = expand(data, var_name);
            ft_free(&var_name);
            if (!var_value) 
            {
                bruh(data, "Failed to allocate memory for var_value", 1);
                return;
            }
            new_word = ft_strjoin_and_free(new_word, var_value);
            ft_free(&var_value);
            i = var_start + var_len;
        }
        else
            new_word = ft_strjoin_char_free(new_word, word[i++]);
    }
    ft_free(&token->word);
    token->word = new_word;
}
