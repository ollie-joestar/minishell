/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:21:09 by hanjkim           #+#    #+#             */
/*   Updated: 2025/02/23 19:00:36 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_tokens_type(t_token *token_list)
{
	t_token	*current;

	current = token_list;
	while (current != NULL)
	{
		set_token_type(current);
		current = current->next;
	}
}

void	split_tokens(t_data *data)
{
	t_token	*current_token;
	t_token	*new_tokens;

	current_token = data->token;
	data->replacements = NULL;
	while (current_token != NULL)
	{
		if (should_split_token(current_token))
		{
			new_tokens = split_token(current_token, data);
			replace_tokens(data, current_token, new_tokens);
			current_token = new_tokens;
		}
		current_token = current_token->next;
	}
}

void	parse_tokens(t_data *data)
{
	char	*input;
	int		start;
	int		end;

	if (!data->line)
		return ;
	input = data->line;
	start = 0;
	end = 0;
	while (input[start] != '\0')
		parse_and_create_token(data, input, &start, &end);
}

void	parse_line(t_data *data)
{
	if (data->token != NULL)
		free_tokens(data);
	data->token = NULL;
	parse_tokens(data);
	set_tokens_type(data->token);
}
