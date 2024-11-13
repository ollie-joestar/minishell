/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:49:14 by hanjkim           #+#    #+#             */
/*   Updated: 2024/11/13 18:49:29 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

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

void	free_token(t_lex_token **token)
{
	if ((*token)->word)
		ft_free(&(*token)->word);
	free(*token);
	*token = NULL;
}

void	check_token_type(t_lex_token *token)
{

	if (*token->word && ft_strncmp(token->word, "<", 2))
		token->type = INPUT;
	else if (*token->word && ft_strncmp(token->word, "<<", 3))
		token->type = HEREDOC;
	else if (*token->word && ft_strncmp(token->word, ">", 2))
		token->type = REPLACE;
	else if (*token->word && ft_strncmp(token->word, ">>", 3))
		token->type = APPEND;
	else if (*token->word && ft_strncmp(token->word, "|", 2))
		token->type = PIPE;
}

void	tokenization(t_data *data)
{
	t_lex_token *token;
	t_lex_token *temp;
	char		*temp_word;

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
		else if (token->type == REPLACE)
		{
			token->left->right = token->right;
			token->right->left = token->left;
			temp = token;
			token = token->right;
			token->type = REPLACE;
			free_token(&temp); //still need the function to free token and set to null
		}
		else if (token->type == APPEND)
		{
			token->left->right = token->right;
			token->right->left = token->left;
			temp = token;
			token = token->right;
			token->type = APPEND;
			free_token(&temp); //still need the function to free token and set to null
		}
		else if (token->type == HEREDOC)
		{
			token->left->right = token->right;
			token->right->left = token->left;
			temp = token;
			token = token->right;
			token->type = HEREDOC;
			temp_word = token->word;
			token->word = here_doc(data, token->word);
			ft_free(&temp_word);
			free_token(&temp); //still need the function to free token and set to null
		}
		token = token->right;
	}
}
