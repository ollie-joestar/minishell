/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:18:27 by hanjkim           #+#    #+#             */
/*   Updated: 2024/11/14 18:21:59 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

// Checks for a single-quote enclosed string and ensures it is properly closed.
int	check_single_quotes(char **input_start, char **input_end)
{
	char	*temp = *input_end;

	if (**input_start == '\'')
	{
		*input_end = *input_start;
		(*input_end)++;
		while (**input_end)
		{
			if (**input_end == '\'')
				return (true);
			(*input_end)++;
		}
	}
	*input_end = temp;
	return (false);
}

// Checks for a double-quote enclosed string and ensures it is properly closed.
int	check_double_quotes(char **input_start, char **input_end)
{
	char	*temp = *input_end;

	if (**input_start == '\"')
	{
		*input_end = *input_start;
		(*input_end)++;
		while (**input_end)
		{
			if (**input_end == '\"')
				return (true);
			(*input_end)++;
		}
	}
	*input_end = temp;
	return (false);
}

/*
// Identifies the type of a token by checking for special symbols or commands.
int	detect_token_type(t_env *env, char **input_start, char **input_end)
{
	int	token_type = check_pipe_symbol(input_start, input_end);

	if (token_type != 0)
		return (token_type);

	token_type = check_input_redirection(input_start, input_end);
	if (token_type != 0)
		return (token_type);

	token_type = check_output_redirection(input_start, input_end);
	if (token_type != 0)
		return (token_type);

	return (identify_general_token_type(env, input_start, input_end));
}*/
