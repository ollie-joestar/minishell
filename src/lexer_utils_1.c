#include "minishell.h"

void	skip_space(char **input)
{
	while (ft_isspace(**input))
		(*input)++;
}

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
/*
//free all tokens later on
void	free_tokens(t_lex_token *lex)
{
	t_token	*temp;

	temp = lex->tokens;
	while (temp)
	{
		lex->token = temp->right;
		free(temp->str);
		free(temp);
		temp = lex->token;
	}
}

void	append_token_to_list(t_data *data, t_lex_token *new_token)
{
	if (!data->token && !data->last_token)
	{
		data->token = new_token;
		data->token->left = NULL;
		data->last_token = new_token;
	}
	else
	{
		new_token->left = data->last_token;
		data->last_token->right = new_token;
		data->last_token = new_token;
	}
}*/
