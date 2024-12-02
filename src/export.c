/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:32:53 by oohnivch          #+#    #+#             */
/*   Updated: 2024/12/02 17:41:59 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_export(t_data *data)
{
	t_envlist	*list;

	list = dup_env(data->env);
	if (!list)
		bruh(data, "Memory allocation failed", 1);
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

void	add_env(t_envlist *env, t_envlist *new)
{
	while (env->next)
		env = env->next;
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

static t_envlist	*create_env(char *name, char *value)
{
	t_envlist	*list;

	list = ft_calloc(1, sizeof(t_envlist));
	if (!list)
		return (NULL);
	list->name = ft_strdup(name);
	list->value = ft_strdup(value);
	if (!list->name)
	{
		ft_putstr_fd("NO NAME\n", 2);
	}
	if (!list->value)
	{
		ft_putstr_fd("NO VALUE\n", 2);
	}
	if (!list->name || !list->value)
	{
		free_env_list(list);
		return (NULL);
	}
	return (list);
}

static void	process_export(t_data *data, t_exec *exec)
{
	t_envlist	*list;
	char		*value;
	char		*name;

	if (ft_strchr(exec->av[1], '='))
	{
		name = ft_substr(exec->av[1], 0, ft_strchr(exec->av[1], '=') - exec->av[1]);
		value = ft_strdup(ft_strchr(exec->av[1], '=') + 1);
	}
	else
	{
		name = ft_strdup(exec->av[1]);
		value = ft_strdup("");
	}
	list = find_env(data->env, name);
	if (list)
		(ft_free(&list->value), list->value = ft_strdup(value));
	else
	{
		list = create_env(name, value);
		if (!list)
			bruh(data, "Memory allocation failed:export.c:95", 1);
		add_env(data->env, list);
	}
	(ft_free(&name), ft_free(&value));
}

void	export(t_data *data, t_exec *exec)
{
	if (ft_arrlen(exec->av) == 1)
		return (print_export(data));
	if (ft_arrlen(exec->av) > 1)
	{
		if (!ft_isalpha(exec->av[1][0]) && exec->av[1][0] != '_')
		{
			ft_putstr_fd("export: '", 2);
			ft_putstr_fd(exec->av[1], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			data->status = 1;
			return ;
		}
		process_export(data, exec);
	}
}
