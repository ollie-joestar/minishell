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


void	insert_token_to_list(t_data *data, t_lex_token *new_token)
{
	if (data->token)
	{
		t_lex_token *tmp = data->token;
		while (tmp->left)
			tmp = tmp->left;
		tmp->left = new_token;
	}
	else
		data->token = new_token;

}
