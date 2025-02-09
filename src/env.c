/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:02:42 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/31 19:21:38 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlist	*parse_env(t_data *data, char **ev)
{
	int			i;
	t_envlist	*tmp;
	char		*name;
	char		*value;

	if (!ev || !*ev)
		return (create_new_env(data));
	tmp = NULL;
	i = -1;
	while (ev[++i])
	{
		name = ft_substr(ev[i], 0, ft_strchr(ev[i], '=') - ev[i]);
		if (!name)
			bruh(data, "Memory allocation failed", 69);
		value = ft_strdup(ft_strchr(ev[i], '=') + 1);
		if (!value)
			(ft_free(&name), bruh(data, "Memory allocation failed", 69));
		if (!tmp)
			tmp = create_env(name, value);
		else
			add_env(tmp, create_env(name, value));
	}
	while (tmp->prev)
		tmp = tmp->prev;
	shlvl(data, tmp);
	return (tmp);
}

void	parse_env_into_ev(t_data *data)
{
	int	i;
	t_envlist	*curr_env_node;
	char	*tmp;

	i = 0;
	if (!data->env)
	{
		data->ev = NULL;
		return ;
	}
	while (data->env->prev)
		data->env = data->env->prev;
	i = env_len(data->env);
	if (data->ev)
		free_arr(&data->ev);
	data->ev = ft_calloc(i + 1, sizeof(char *));
	if (!data->ev)
		bruh(data, "Malloc error parse_env_into_ev:67", 69);
	i = 0;
	curr_env_node = data->env;
	while (curr_env_node)
	{
		tmp = data->ev[i];
		data->ev[i] = ft_strjoin(curr_env_node->name, "=");
		if (!data->ev[i])
			bruh(data, "Malloc error parse_env_into_ev:75", 69);
		ft_free(&tmp);
		tmp = data->ev[i];
		/*data->ev[i] = ft_strjoin(data->ev[i], curr_env_node->value);*/
		data->ev[i] = join2(tmp, curr_env_node->value);
		if (!data->ev[i] && curr_env_node->value)
			bruh(data, "Malloc error parse_env_into_ev:80", 69);
		ft_free(&tmp);
		curr_env_node = curr_env_node->next;
		i++;
	}
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
		ft_printf("%s=%s\n", list->name, list->value);
		list = list->next;
	}
}

void	underscore(t_data *data, t_exec *exec)
{
	t_envlist	*list;
	char		*value;
	int			i;

	if (exec_len(data->exec) > 1)
		if (lpid(data))
			return ;
	i = ft_arrlen(exec->av) - 1;
	if (i < 0)
		value = ft_strdup("");
	else
		value = ft_strdup(exec->av[i]);
	list = find_env(data->env, "_");
	if (list)
		(ft_free(&list->value), list->value = value);
	else
	{
		list = create_env("_", value);
		if (!list)
			bruh(data, "Malloc fail env.c:125", 69);
		add_env(data->env, list);
		ft_free(&value);
	}
}
