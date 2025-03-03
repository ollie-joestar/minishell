/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:21:09 by hanjkim           #+#    #+#             */
/*   Updated: 2025/03/03 16:38:07 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Cycle through the token list and set it's fate (type)
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

// Split tokens into multiple tokens if word was quoted or not
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

// Go through the input and decide where to make tokens
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
		parse_make_token(data, input, &start, &end);
}

// Main lexer function to parse the line
void	parse_line(t_data *data)
{
	if (data->token != NULL)
		free_tokens(data);
	data->token = NULL;
	parse_tokens(data);
	set_tokens_type(data->token);
}
