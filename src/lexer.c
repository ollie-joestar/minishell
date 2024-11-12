#include "minishell.h"
/*
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
*/
// Tokenizes the entire input string to break it down into individual tokens
/*t_token	*tokenize_input_string(t_token *token)*/
/*{*/
/*	char	*input_start = env->input_line;*/
/**/
/*	env->last_token = NULL;*/
/**/
/*	while (*input_start)*/
/*	{*/
/*		skip_whitespace(&input_start);*/
/*		if (!*input_start)*/
/*			break;*/
/*		if (!append_token(env, &input_start))*/
/*			return (free_token_list(env), NULL);*/
/*	}*/
/**/
/*	if (!append_token(token, &input_start))*/
/*		return (free_token_list(env), NULL);*/
/**/
/*	return (token->token_list_head);*/
/*}*/
/**/

t_lex_token	*create_token(int type, char *str)
{
	t_lex_token	*token;

	token = (t_lex_token *)malloc(sizeof(t_lex_token));
	if (!token)
	{
		free(str);
		return (NULL);
	}
	token->type = type;
	token->word = str;
	token->right = NULL;
	token->left = NULL;
	return (token);
}

void	tokenization(t_data *data)
{
	int		i;
	char	**av;
	t_lex_token	*temp;

	av = ft_split(data->line, ' ');
	if (!av)
		bruh(data, "Failed to split line", 1);
	i = -1;
	while (av[++i])
	{
		temp = data->token;
		data->token = create_token(CMD, av[i]);
		if (!data->token)
			bruh(data, "Failed to create token", 1);
		if (temp) 
		{
			temp->right = data->token;
			data->token->left = temp;
		}
	}
}
/*
void	tokenization(t_data *data)
{
	char	*start;

	start = data->line;
	data->last_token = NULL;
	if (*start)
	{
		skip_space(&start);
		if (!*start)
			return ;
//		if (!add_token(data, &start))
//			return (free_tokens(data), NULL);
	}
	return ;
}*/
