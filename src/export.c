/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:32:53 by oohnivch          #+#    #+#             */
/*   Updated: 2025/02/13 15:33:05 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_export(t_data *data)
{
	t_envlist	*list;

	if (!data->env)
		ft_printerr("No env for export\n");
	list = dup_env(data->env);
	if (!list)
		bruh(data, "Memory allocation failed", 69);
	sort_env(list);
	while (list->prev)
		list = list->prev;
	while (list)
	{
		if (ft_strncmp(list->name, "_", 2))
			ft_printf("declare -x %s=\"%s\"\n", list->name, list->value);
			/*ft_printf("export %s=\"%s\"\n", list->name, list->value);*/
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

t_envlist	*create_env(char *name, char *value)
{
	t_envlist	*list;

	list = ft_calloc(1, sizeof(t_envlist));
	if (!list)
		return (NULL);
	list->name = ft_strdup(name);
	list->value = ft_strdup(value);
	(ft_free(&name), ft_free(&value));
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

static void	process_export(t_data *data, t_exec *exec, int j)
{
	t_envlist	*list;
	char		*new_name;
	char		*new_value;

	if (ft_strchr(exec->av[j], '='))
	{
		new_name = ft_substr(exec->av[j], 0, ft_strchr(exec->av[j], '=') - exec->av[j]);
		new_value = ft_strdup(ft_strchr(exec->av[j], '=') + 1);
	}
	else
	{
		new_name = ft_strdup(exec->av[j]);
		new_value = ft_strdup("");
	}
	list = find_env(data->env, new_name);
	if (list && ft_strchr(exec->av[j], '='))
		(ft_free(&list->value), list->value = ft_strdup(new_value));
	else if (ft_strchr(exec->av[j], '='))
	{
		list = create_env(new_name, new_value);
		new_name = NULL;
		new_value = NULL;
		if (!list)
			bruh(data, "Memory allocation failed:export.c:102", 69);
		add_env(data->env, list);
	}
	(ft_free(&new_name), ft_free(&new_value));
}

void	export(t_data *data, t_exec *exec)
{
	int	i;
	int	j;

	/*ft_printf("avlen: %d\n", ft_arrlen(exec->av));*/
	if (ft_arrlen(exec->av) == 1)
		return (print_export(data));
	j = 0;
	while (exec->av[++j])
	{
		if (exec->av[j][0] && (exec->av[j][0] != '_' && !ft_isalpha(exec->av[j][0])))
		{
			ft_printerr("minishell: export: `%s': not a valid identifier\n", exec->av[j]);
			data->status = 1;
			return ;
		}
		i = 1;
		while (exec->av[j][i] && exec->av[j][i] != '=')
		{
			if (!ft_isalnum(exec->av[j][i]) && exec->av[j][i] != '_')
			{
				ft_printerr("minishell: export: `%s': not a valid identifier\n", exec->av[1]);
				data->status = 1;
				return ;
			}
			i++;
		}
		process_export(data, exec, j);
	}
}
