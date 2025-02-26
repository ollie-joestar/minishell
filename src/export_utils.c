/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:43:33 by oohnivch          #+#    #+#             */
/*   Updated: 2025/02/27 15:08:37 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_data *data)
{
	t_envlist	*list;

	if (!data->env)
		mspec("No env for export\n");
	list = dup_env(data->env);
	if (!list)
		bruh(data, "Memory allocation failed", 69);
	list = sort_env(list);
	while (list->prev)
		list = list->prev;
	while (list)
	{
		if (ft_strncmp(list->name, "_", 2))
		{
			if (pid(data) == 0)
				safe_print_export(data, list->name, list->value);
			else
				ft_printf("declare -x %s=\"%s\"\n", list->name, list->value);
		}
		if (!list->next)
			break ;
		list = list->next;
	}
	free_env_list(list);
}

void	add_env(t_envlist *env, t_envlist *new)
{
	if (!env || !new)
		return ;
	while (env->next)
		env = env->next;
	while (new->prev)
		new = new->prev;
	env->next = new;
	new->prev = env;
}

t_envlist	*find_env(t_envlist *env, char *name)
{
	while (env->prev)
		env = env->prev;
	while (env)
	{
		if (!ft_strncmp(env->name, name, ft_strlen(env->name) + 1))
			return (env);
		env = env->next;
	}
	return (NULL);
}

t_envlist	*create_env(char *name, char *value)
{
	t_envlist	*list;

	list = ft_calloc(1, sizeof(t_envlist));
	if (!list)
		return (NULL);
	list->name = ft_strdup(name);
	list->value = ft_strdup(value);
	if (!list->name)
		ft_putstr_fd("NO NAME\n", 2);
	if (!list->value)
		ft_putstr_fd("NO VALUE\n", 2);
	if (!list->name || !list->value)
	{
		free_env_list(list);
		return (NULL);
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
