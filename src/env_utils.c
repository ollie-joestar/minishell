/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:35:47 by oohnivch          #+#    #+#             */
/*   Updated: 2025/03/03 16:35:50 by oohnivch         ###   ########.fr       */
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

	while (!sorted_env(list))
	{
		while (list->prev)
			list = list->prev;
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
	while (list->prev)
		list = list->prev;
	return (list);
}

void	print_env(t_data *data)
{
	t_envlist	*list;

	if (!data->env)
		return ;
	while (data->env->prev)
		data->env = data->env->prev;
	list = data->env;
	while (list)
	{
		if (list->value)
		{
			if (pid(data) == 0)
				safe_print_env(data, list->name, list->value);
			else
				ft_printf("%s=%s\n", list->name, list->value);
		}
		list = list->next;
	}
}
