/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:29:57 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/14 11:49:27 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	argv_size(t_lex_token *token)
{
	size_t	size;

	size = 0;
	while (token && token->type == WORD)
	{
		size++;
		token = token->right;
	}
	return (size);
}

char	**create_argv(t_data *data, t_lex_token *token)
{
	char	**av;
	size_t	size;
	int		i;

	size = argv_size(token);
	av = ft_calloc(size + 1, sizeof(char *));
	if (!av)
		return (NULL);
	i = 0;
	while (token->type == WORD)
	{
		av[i] = ft_strdup(token->word);
		if (!av[i])
			return (free_arr(av), NULL);
		data->token = token;
		token = token->right;
		i++;
	}
	return (av);
}
