/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:28:15 by hanjkim           #+#    #+#             */
/*   Updated: 2024/11/18 14:40:45 by oohnivch         ###   ########.fr       */
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

	expanded_word = process_word_expansion(data, word);
	if (!expanded_word)
		bruh(data, "Failed to expand line", 1);
	tokens = ft_split(expanded_word, ' ');
	if (!tokens)
		bruh(data, "Failed to split expanded line", 1);
	return (tokens);
}

void	insert_expanded_tokens(t_data *data, t_token **current)
{
	t_token	*old_token;
	t_token	*new_tokens;
	t_token	*last_new_token;
	t_token	*temp;
	char	**expanded_words;
	int		i;
	
	old_token = *current;
	i = -1;
	expanded_words = expand_token_to_words(data, old_token->word);
	if (!expanded_words)
		bruh(data, "Failed to expand token", 1);
	while(expanded_words[++i])
	{
		temp = create_token();
		if (!temp)
			bruh(data, "Failed to create token", 1);
		temp->word = expanded_words[i];
		if (!new_tokens)
			new_tokens = temp;
		else
			last_new_token->right = temp;
		temp->left = last_new_token;
		last_new_token = temp;
	}
	free_arr(expanded_words);
	update_token_links(new_tokens, last_new_token, old_token);
	*current = new_tokens;
	free_old_token(old_token);
}

void	check_for_needed_expansion(t_data *data)
{
	t_token	*current;

	current = data->token;
	while (current)
	{
		if (requires_expansion(current->word))
			insert_expanded_tokens(data, &current);
			/*current = insert_expanded_tokens(data, current);*/
		current = current->right;
	}
}
