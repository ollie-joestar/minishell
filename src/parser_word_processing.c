/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_word_processing.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:32:27 by hanjkim           #+#    #+#             */
/*   Updated: 2024/11/21 19:37:10 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_start_index(int current_index)
{
	return(current_index + 1);
}

int find_end_index(t_token *token, int start_index, char quote)
{
	int end_index;

	end_index = start_index;
	while (token->word[end_index] && token->word[end_index] != quote)
		end_index++;
	if (token->word[end_index] == quote)
		return (end_index);
	return (end_index);
}

void	process_env_variable(t_data *data, char **buffer, int *index)
{
	int		start_index;
	int		end_index;
	char	*var_name;
	char	*var_value;
	char	*temp;

	start_index = (*index) + 1;
	while (ft_isalnum(data->token->word[*index]) || data->token->word[*index] == '_')
		(*index)++;
	end_index = *index;
	var_name = ft_substr(data->token->word, start_index, end_index - start_index);
	if (!var_name)
		return;
	var_value = expand(data, var_name);
	free(var_name);
	if (!var_value)
		return;
	temp = *buffer;
	*buffer = ft_strjoin(*buffer, var_value);
	free(temp);
	free(var_value);
}

char	*process_word_expansion(t_data *data, char *word)
{
	char	*expanded_word;
	int		i;
	char	temp[2];
	char	*new_expanded_word;

	ft_printf("entered process_word_expansion\n");
	/*ft_printf("word: %s\n", word);*/
	i = -1;
	expanded_word = ft_calloc(1, sizeof(char));
	if (!expanded_word)
		return (NULL);
	while (word[++i])
	{
		if (word[i] == SQ)
			read_single_quotes(&expanded_word, data->token, &i);
		else if (word[i] == DQ)
			read_double_quotes(data, data->token, &expanded_word, &i);
		else if (word[i] == DOLLAR)
			process_env_variable(data, &expanded_word, &i);
		else
		{
			temp[0] = word[i];
			temp[1] = '\0';
			new_expanded_word = ft_strjoin(expanded_word, temp);
			free(expanded_word);
			expanded_word = new_expanded_word;
		}
	}
	return (expanded_word);
}
