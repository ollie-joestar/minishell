/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:32:53 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/26 12:33:54 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	sorted_env(t_envlist *list)
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
	return (0);
}

static void	swap_nodes(t_envlist *first, t_envlist *second)
{
	t_envlist	*tmp;

	tmp = first->prev;
	first->prev = second;
	first->next = second->next;
	second->prev = tmp;
	second->next = first;
}

static void	sort_env(t_envlist *list)
{
	t_envlist	*tmp;

	while (list->prev)
		list = list->prev;
	while (!sorted_env(list))
	{
		tmp = list;
		while (tmp && tmp->next)
		{
			if (ft_strncmp(tmp->name, tmp->next->name, ft_strlen(tmp->name)) > 0)
				swap_nodes(tmp, tmp->next);
			tmp = tmp->next;
		}
	}
}

static void print_export(t_envlist *list)
{
	sort_env(list);
	while (list->prev)
		list = list->prev;
	while (list)
	{
		if (ft_strncmp(list->name, "_", 2))
			ft_printf("declare -x %s=\"%s\"\n", list->name, list->value);
		list = list->next;	
	}
	free_env_list(list);
}

t_envlist *dup_env(t_envlist *list)
{
	t_envlist	*new;
	t_envlist	*tmp;

	new = NULL;
	while (list->prev)
		list = list->prev;
	while (list)
	{
		tmp = ft_calloc(1, sizeof(t_envlist));
		if (!tmp)
			return (NULL);
		tmp->name = ft_strdup(list->name);
		tmp->value = ft_strdup(list->value);
		if (!tmp->name || !tmp->value)
			return (free_env_list(tmp), free_env_list(new), NULL);
		if (new)
			(new->next = tmp, tmp->prev = new);
		new = tmp;
		list = list->next;
	}
	while (new->prev)
		new = new->prev;
	return (new);
}

void	export(t_data *data, t_exec *exec)
{
	t_envlist	*list;

	ft_printf("exporting env\n");
	if (ft_arrlen(exec->av) == 1)
	{
		ft_printf("duping env\n");
		list = dup_env(data->env);
		ft_printf("duped env\n");
		if (!list)
			bruh(data, "Memory allocation failed", 1);
		print_export(list);
	}
}
