/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:29:57 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/21 17:12:01 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	argv_size(t_token *token)
{
	size_t	size;

	size = 0;
	while (token && token->type == WORD)
	{
		size++;
		token = token->next;
	}
	return (size);
}

char	**create_argv(t_data *data, t_token *token)
{
	char	**av;
	size_t	size;
	int		i;

	size = argv_size(token);
	av = ft_calloc(size + 1, sizeof(char *));
	if (!av)
		return (NULL);
	i = 0;
	while (token && token->type == WORD)
	{
		/*if (!token->word)*/
		/*	return (av);*/
		av[i] = ft_strdup(token->word);
		if (!av[i])
			return (free_arr(&av), NULL);
		data->token = token;
		token = token->next;
		i++;
	}
	return (av);
}
