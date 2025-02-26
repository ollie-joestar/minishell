/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:17:06 by oohnivch          #+#    #+#             */
/*   Updated: 2025/02/26 18:48:29 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	env_len(t_envlist *env)
{
	size_t	len;

	len = 0;
	if (!env)
		return (0);
	while (env->prev)
		env = env->prev;
	while (env)
	{
		len++;
		env = env->next;
	}
	return (len);
}

int	sorted_env(t_envlist *list)
{
	t_envlist	*tmp;

	while (list->prev)
		list = list->prev;
	while (list && list->next)
	{
		tmp = list->next;
		if (ft_strncmp(list->name, tmp->name, ft_strlen(list->name)) > 0)
			return (0);
		list = list->next;
	}
	return (1);
}

static void	swap_env_nodes(t_envlist *first, t_envlist *second)
{
	t_envlist	*tmp;

	tmp = first->prev;
	first->prev = second;
	first->next = second->next;
	second->prev = tmp;
	if (tmp)
		tmp->next = second;
	if (second->next)
		second->next->prev = first;
	second->next = first;
}

t_envlist	*sort_env(t_envlist *list)
{
	t_envlist	*frst;
	t_envlist	*scnd;

	while (list->prev)
		list = list->prev;
	while (!sorted_env(list))
	{
		frst = list;
		while (frst && frst->next)
		{
			scnd = frst->next;
			if (ft_strncmp(frst->name, scnd->name, ft_strlen(frst->name)) > 0)
			{
				swap_env_nodes(frst, scnd);
				break ;
			}
			frst = frst->next;
		}
	}
	return (list);
}

t_envlist	*dup_env(t_envlist *list)
{
	t_envlist	*new;
	t_envlist	*tmp;

	new = NULL;
	while (list)
	{
		tmp = ft_calloc(1, sizeof(t_envlist));
		if (!tmp)
			return (free_env_list(new), NULL);
		tmp->name = ft_strdup(list->name);
		tmp->value = ft_strdup(list->value);
		if (!tmp->name || !tmp->value)
			return (free_env_list(tmp), free_env_list(new), NULL);
		if (new)
		{
			new->next = tmp;
			tmp->prev = new;
		}
		new = tmp;
		list = list->next;
	}
	while (new->prev)
		new = new->prev;
	return (new);
}
