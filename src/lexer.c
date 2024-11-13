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

t_lex_token	*create_token(void)
{
	t_lex_token	*token;

	token = (t_lex_token *)ft_calloc(1, (sizeof(t_lex_token)));
	return (token);
}

void	init_tokens(t_data *data)
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
		temp = create_token();
		if (!temp)
			bruh(data, "Failed to create token", 1);
		temp->word = av[i];
		if (!data->token)
			data->token = temp;
		if(data->token)
		{
			data->token->right = temp;
			temp->left = data->token;
			data->token = temp;
		}
	}
}

void	check_token_type(t_lex_token *token)
{

	if (*token->word && ft_strncmp(token->word, "<", 2))
		token->type = INPUT;
	else if (*token->word && ft_strncmp(token->word, "<<", 3))
		token->type = INPUT;
	else if (*token->word && ft_strncmp(token->word, ">", 2))
		token->type = OUTPUT;
	else if (*token->word && ft_strncmp(token->word, ">>", 3))
		token->type = OUTPUT;
	else if (*token->word && ft_strncmp(token->word, "|", 2))
		token->type = PIPE;
}
		
void	tokenization(t_data *data)
{
	t_lex_token *token;
	t_lex_token *temp;

	while (data->token && data->token->left)
		data->token = data->token->left;
	token = data->token;
	while (token)
	{
		check_token_type(token);
		if (token->type == INPUT)
		{
			token->left->right = token->right;
			token->right->left = token->left;
			temp = token;
			token = token->right;
			token->type = INPUT;
			free_token(&temp); //still need the function to free token and set to null
		}
		else if (token->type == OUTPUT)
		{
			token->left->right = token->right;
			token->right->left = token->left;
			temp = token;
			token = token->right;
			token->type = OUTPUT;
			free_token(&temp); //still need the function to free token and set to null
		}
		token = token->right;
	}
}


