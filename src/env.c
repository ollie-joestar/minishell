/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:02:42 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/21 19:51:57 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlist	*parse_env(t_data *data, char **ev)
{
	int	i;
	t_envlist	*list;
	t_envlist	*tmp;

	if (!ev || !*ev)
		return (create_new_env(data));
	tmp = NULL;
	i = -1;
	while (ev[++i])
	{
		list = ft_calloc(1, sizeof(t_envlist));
		if (!list)
			bruh(data, "Memory allocation failed", 69);
		list->name = ft_substr(ev[i], 0, ft_strchr(ev[i], '=') - ev[i]);
		if (!list->name)
			(free_env_list(list), bruh(data, "Memory allocation failed", 69));
		list->value = ft_strdup(ft_strchr(ev[i], '=') + 1);
		if (!list->value)
			(free_env_list(list), bruh(data, "Memory allocation failed", 69));
		if (tmp)
		{
			tmp->next = list;
			list->prev = tmp;
		}
		tmp = list;
	}
	while (tmp->prev)
		tmp = tmp->prev;
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
		bruh(data, "Memory allocation failed", 69);
	i = 0;
	curr_env_node = data->env;
	while (curr_env_node)
	{
		tmp = data->ev[i];
		data->ev[i] = ft_strjoin(curr_env_node->name, "=");
		if (!data->ev[i])
			bruh(data, "Memory allocation failed", 69);
		ft_free(&tmp);
		tmp = data->ev[i];
		data->ev[i] = ft_strjoin(data->ev[i], curr_env_node->value);
		if (!data->ev[i])
			bruh(data, "Memory allocation failed", 69);
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
