/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:50:38 by oohnivch          #+#    #+#             */
/*   Updated: 2025/03/03 16:44:05 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlist	*parse_env_subprocess(t_data *dt, char **n, char **v, t_envlist *l)
{
	t_envlist	*node;

	node = NULL;
	if (!l)
		l = create_env(*n, *v);
	else
	{
		node = create_env(*n, *v);
		if (!node)
			(free_env_list(l), ft_free(n), ft_free(v),
				bruh(dt, "Malloc failed""env.c:27", 69));
		add_env(l, node);
	}
	(ft_free(n), ft_free(v));
	if (!l)
		bruh(dt, "Malloc failed env.c:32", 69);
	return (l);
}

t_envlist	*parse_env_process(t_data *data, char **ev)
{
	int			i;
	t_envlist	*list;
	char		*name;
	char		*value;

	i = -1;
	list = NULL;
	name = NULL;
	value = NULL;
	while (ev[++i])
	{
		name = ft_substr(ev[i], 0, ft_strchr(ev[i], '=') - ev[i]);
		value = ft_strdup(ft_strchr(ev[i], '=') + 1);
		if (!name || !value)
			(free_env_list(list), ft_free(&name), ft_free(&value),
				bruh(data, "Memory allocation failed", 69));
		list = parse_env_subprocess(data, &name, &value, list);
		if (!list)
			bruh(data, "Memory allocation failed", 69);
	}
	while (list && list->prev)
		list = list->prev;
	return (list);
}

t_envlist	*parse_env(t_data *data, char **ev)
{
	t_envlist	*list;

	if (!ev || !*ev)
		return (create_new_env(data));
	else
		list = parse_env_process(data, ev);
	if (!list)
		bruh(data, "Memory allocation failed", 69);
	shlvl(data, list);
	if (!list)
		bruh(data, "Memory allocation failed", 69);
	return (list);
}

void	parse_env_into_ev_process(t_data *data, t_envlist *node, int i)
{
	char	*tmp;

	tmp = data->ev[i];
	data->ev[i] = ft_strjoin(node->name, "=");
	if (!data->ev[i])
		bruh(data, "Strjoin failed env.c:62", 69);
	ft_free(&tmp);
	tmp = data->ev[i];
	data->ev[i] = join2(tmp, node->value);
	if (!data->ev[i] && node->value)
		bruh(data, "Join2 failed env.c:67", 69);
	ft_free(&tmp);
}

void	parse_env_into_ev(t_data *data)
{
	int			i;
	t_envlist	*curr_env_node;

	i = 0;
	if (!data->env)
		return (free_arr(&data->ev));
	i = env_len(data->env);
	free_arr(&data->ev);
	data->ev = ft_calloc(i + 1, sizeof(char *));
	if (!data->ev)
		bruh(data, "Malloc error parse_env_into_ev:67", 69);
	i = -1;
	curr_env_node = data->env;
	while (curr_env_node)
	{
		parse_env_into_ev_process(data, curr_env_node, ++i);
		curr_env_node = curr_env_node->next;
	}
}
