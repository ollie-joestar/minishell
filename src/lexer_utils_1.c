#include "minishell.h"

void	skip_space(char **input)
{
	while (ft_isspace(**input))
		(*input)++;
}
/*
void	ft_strncpy(char	*dest, const char *str, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dest;

	if (!s)
		return (NULL);
	dest = malloc(n + 1);
	if (!dest)
		return (NULL);
	ft_strncpy(dest, s, n);
	return (dest);
}

void	free_tokens(t_lexer_context *lex)
{
	t_token	*temp;

	temp = lex->tokens;
	while (temp)
	{
		lex->tokens = temp->right;
		free(temp->str);
		free(temp);
		temp = lex->tokens;
	}
}

void	append_token_to_list(t_data *data, t_lex_token *new_token)
{
	if (!data->tokens && !data->last_token)
	{
		data->tokens = new_token;
		data->tokens->left = NULL;
		data->last_token = new_token;
	}
	else
	{
		new_token->left = data->last_token;
		data->last_token->right = new_token;
		data->last_token = new_token;
	}
}*/
