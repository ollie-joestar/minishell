/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:21:09 by hanjkim           #+#    #+#             */
/*   Updated: 2024/12/01 16:58:31 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_spaces(char *input, int *i)
{
	while ((input[*i] == ' ' || input[*i] == '\t'))
		(*i)++;
}

void	parse_and_create_token(t_data *data, char *input, int *start, int *end)
{
	char	*token_str;
	t_token	*new_token;

	skip_spaces(input, start);
	*end = *start;
	if (input[*start] == '\0')
		return ;
	token_str = parse_word_token(input, start, end, data);
	if (!token_str)
		return ;
	new_token = create_token(token_str, data->is_currently_quoted,
			data->is_currently_double_quoted);
	if (new_token)
		add_token_to_end(&(data->token), new_token);
	free(token_str);
	*start = *end;
}

void	parse_tokens(t_data *data)
{
	char	*input;
	int		start;
	int		end;

	input = data->line;
	start = 0;
	end = 0;
	while (input[start] != '\0')
		parse_and_create_token(data, input, &start, &end);
}

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

void	parse_line(t_data *data)
{
	data->token = NULL;
	parse_tokens(data);
	split_tokens(data);
	replace_tokens(data);
	set_tokens_type(data->token);
}
