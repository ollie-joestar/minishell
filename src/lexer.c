/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:21:09 by hanjkim           #+#    #+#             */
/*   Updated: 2024/11/28 23:51:57 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_token(t_data *data, char **start, char **end, bool *single_or_double)
{
	char	*token_str;
	t_token	*new_token;

	if (**end == SQ || **end == DQ)
	{
		token_str = parse_quoted_token(start, end, single_or_double);
		new_token = create_token(token_str, true, *single_or_double);
	}
	else
	{
		token_str = parse_regular_token(start, end);
		new_token = create_token(token_str, false, false);
	}
	add_token_to_end(&(data->token), new_token);
	ft_free(&token_str);
}

void	parse_tokens(t_data *data)
{
	char	*start;
	char	*end;
	bool	single_or_double;

	start = data->line;
	end = start;
	single_or_double = false;
	while (*end != '\0')
	{
		skip_spaces(&end);
		start = end;
		if (*end == '\0')
			break ;
		parse_token(data, &start, &end, &single_or_double);
	}
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
	set_tokens_type(data->token);
}
