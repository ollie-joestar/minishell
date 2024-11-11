#include "minishell.h"

t_token	*create_token(int type, char *str)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
	{
		free(str);
		return (NULL);
	}
	token->type = type;
	token->str = str;
	token->right = NULL;
	token->left = NULL;
	return (token);
}

// Tokenizes the entire input string to break it down into individual tokens
t_token	*tokenize_input_string(t_token *token)
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

	if (!append_token(token, &input_start))
		return (free_token_list(env), NULL);

	return (token->token_list_head);
}
