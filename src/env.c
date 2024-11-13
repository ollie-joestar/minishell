/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:02:42 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/13 14:23:24 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_env(t_data *data, char **ev)
{
	int	i;
	t_envlist	*list;

	i = -1;
	if (!ev || !*ev)
		return ;
	while (ev[++i])
	{
		list = ft_calloc(1, sizeof(t_envlist));
		if (!list)
			bruh(data, "Memory allocation failed", 1);
		list->name = ft_substr(ev[i], 0, ft_strchr(ev[i], '=') - ev[i]);
		if (!list->name)
			bruh(data, "Memory allocation failed", 1);
		list->value = ft_strdup(ft_strchr(ev[i], '=') + 1);
		if (!list->value)
			bruh(data, "Memory allocation failed", 1);
		if (!data->env)
			data->env = list;
		else
		{
			list->prev = data->env;
			data->env->next = list;
			data->env = list;
		}
	}
}

void	parse_env_into_ev(t_data *data)
{
	int	i;
	t_envlist	*curr_env_node;

	i = 0;
	if (!data->env)
		return ;
	while (data->env->prev)
		data->env = data->env->prev;
	i = env_len(data->env);
	data->ev = ft_calloc(i + 1, sizeof(char *));
	if (!data->ev)
		bruh(data, "Memory allocation failed", 1);
	i = 0;
	curr_env_node = data->env;
	while (curr_env_node)
	{
		data->ev[i] = ft_strjoin(curr_env_node->name, "=");
		if (!data->ev[i])
			bruh(data, "Memory allocation failed", 1);
		data->ev[i] = ft_strjoin(data->ev[i], curr_env_node->value);
		if (!data->ev[i])
			bruh(data, "Memory allocation failed", 1);
		curr_env_node = curr_env_node->next;
		i++;
	}
}

void	print_env(t_data *data)
{
	t_envlist	*list;

	list = data->env;
	while (list)
	{
		printf("%s=%s\n", list->name, list->value);
		list = list->prev;
	}
}
