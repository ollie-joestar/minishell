/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:18:27 by hanjkim           #+#    #+#             */
/*   Updated: 2024/11/19 16:15:38 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_single_quotes(char **buffer, t_token *token, int *i)
{
	int start_index;
	int end_index;
	char *str_to_join;
	char *temp;

	start_index = find_start_index(*i);
	end_index = find_end_index(token, start_index, SQ);
	if (end_index == -1)
		return ;
	str_to_join = ft_substr(token->word, start_index, end_index - start_index);
	if (!str_to_join)
		return;
	temp = *buffer;
	*buffer = ft_strjoin(*buffer, str_to_join);
	free(temp);
	free(str_to_join);
	*i = end_index;
}

void	read_double_quotes(t_data *data, t_token *token, char **buffer, int *i)
{
	int start_index;
	int end_index;
	char *str_to_join;
	char *temp;

	start_index = find_start_index(*i);
	end_index = find_end_index(data->token, start_index, DQ);
	while (start_index < end_index)
	{
		if (token->word[start_index] == DOLLAR)
			process_env_variable(data, buffer, i);
		else
		{
			str_to_join = ft_substr(token->word, start_index, end_index - start_index);
			if (!str_to_join)
				return;
			temp = *buffer;
			*buffer = ft_strjoin(*buffer, str_to_join);
			free(temp);
			free(str_to_join);
			start_index++;
		}
	}
	*i = end_index;
}
