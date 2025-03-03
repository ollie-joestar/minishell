/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:34:10 by oohnivch          #+#    #+#             */
/*   Updated: 2025/03/03 16:34:14 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_avlist	*first_av_list(t_avlist *av_list)
{
	while (av_list && av_list->prev)
		av_list = av_list->prev;
	return (av_list);
}

t_avlist	*next_valid_av_list(t_avlist *av_list)
{
	while (av_list)
	{
		if (*av_list->arg)
			return (av_list);
		av_list = av_list->next;
	}
	return (NULL);
}

void	add_to_av_list(t_data *data, t_exec *exec, t_token *token)
{
	t_avlist	*av_list;

	if (!token)
		return (mspec("No token argv.c:39\n"));
	av_list = ft_calloc(1, sizeof(t_avlist));
	if (!av_list)
		bruh(data, "Malloc failed argv.c:50", 69);
	if (exec->av_list)
	{
		exec->av_list->next = av_list;
		av_list->prev = exec->av_list;
	}
	exec->av_list = av_list;
	av_list->arg = ft_strdup(token->word);
	if (!av_list->arg)
		bruh(data, "Malloc failed argv.c:53", 69);
}

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
