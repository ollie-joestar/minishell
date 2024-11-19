/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:28:15 by hanjkim           #+#    #+#             */
/*   Updated: 2024/11/19 12:10:42 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	requires_expansion(char *word)
{
	return (ft_strchr(word, DOLLAR) || ft_strchr(word, SQ) || ft_strchr(word, DQ));
}

char	**expand_token_to_words(t_data *data, char *word)
{
	char	*expanded_word;
	char	**tokens;

	bruh(data, "Failed to expand token words", 1);
	expanded_word = process_word_expansion(data, word);
	if (!expanded_word)
		bruh(data, "Failed to expand line", 1);
	tokens = ft_split(expanded_word, ' ');
	if (!tokens)
		bruh(data, "Failed to split expanded line", 1);
	return (tokens);
}

t_token *expand_token(t_data *data, char *word)
{
    char    **expanded_words;
    t_token *new_tokens;

    expanded_words = expand_token_to_words(data, word);
    if (!expanded_words)
        bruh(data, "Failed to expand token", 1);
    new_tokens = init_tokens(data, expanded_words);
    if (!new_tokens)
    {
        free_arr(&expanded_words);
        bruh(data, "Failed to create expanded tokens", 1);
    }
    free(expanded_words);
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

void check_for_needed_expansion(t_data *data)
{
    t_token *current;
    t_token *next;
    t_token *expanded_tokens;

    /*printf("assigning current\n");*/
    current = data->token;
    /*printf("assigned current\n");*/
    while (current)
    {
        /*printf("current->word: %s\n", current->word);*/
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
}
