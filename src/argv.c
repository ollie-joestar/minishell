/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:29:57 by oohnivch          #+#    #+#             */
/*   Updated: 2025/02/17 12:47:00 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_avlist	*first_av_list(t_avlist *av_list)
{
	while (av_list && av_list->prev)
		av_list = av_list->prev;
	/*while (!*av_list->arg)*/
	/*{*/
	/*	if (!av_list->next)*/
	/*		break ;*/
	/*	av_list = av_list->next;*/
	/*}*/
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
	{
		ft_printerr("No token argv.c:45\n");
		return ;
	}
	av_list = ft_calloc(1, sizeof(t_avlist));
	if (!av_list)
		bruh(data, "Malloc failed argv.c:50", 69);
	av_list->arg = ft_strdup(token->word);
	if (!av_list->arg)
		bruh(data, "Malloc failed argv.c:53", 69);
	if (exec->av_list)
	{
		exec->av_list->next = av_list;
		av_list->prev = exec->av_list;
	}
	exec->av_list = av_list;
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

/*char	**create_argv(t_data *data, t_token *token)*/
/*{*/
/*	char	**av;*/
/*	size_t	size;*/
/*	int		i;*/
/**/
/*	size = argv_size(token);*/
/*	av = ft_calloc(size + 1, sizeof(char *));*/
/*	if (!av)*/
/*		return (NULL);*/
/*	i = 0;*/
/*	while (token && token->type == WORD)*/
/*	{*/
		/*if (!token->word)*/
		/*	return (av);*/
/*		av[i] = ft_strdup(token->word);*/
/*		if (!av[i])*/
/*			return (free_arr(&av), NULL);*/
/*		data->token = token;*/
/*		token = token->next;*/
/*		i++;*/
/*	}*/
/*	return (av);*/
/*}*/
