/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:52:39 by oohnivch          #+#    #+#             */
/*   Updated: 2024/10/23 14:56:26 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// Initializes a new token with its type and string value
void	initialize_token(t_token *token, char *content, int token_type)
{
	token->type = token_type;
	token->content = content;
	token->right = NULL;
}

// Creates a new token and initializes its values and allocating memory
t_token	*create_new_token(int token_type, char *content)
{
	t_token	*token = (t_token *)malloc(sizeof(t_token));

	if (!token)
		return (free(content), NULL);

	initialize_token(token, content, token_type);
	return (token);
}

// Tokenizes the entire input string to break it down into individual tokens
t_token	*tokenize_input_string(t_env *env)
{
	char	*input_start = env->input_line;

	env->last_token = NULL;

	while (*input_start)
	{
		skip_whitespace(&input_start);
		if (!*input_start)
			break;
		if (!append_token(env, &input_start))
			return (free_token_list(env), NULL);
	}

	if (!append_token(env, &input_start))
		return (free_token_list(env), NULL);

	return (env->token_list_head);
}
