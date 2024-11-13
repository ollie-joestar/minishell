/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:39:11 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/13 14:07:00 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_slash(char **path)
{
	int		i;
	char	*tmp;

	i = -1;
	if (!path || !*path)
		return ;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			return ;
		ft_free(&path[i]);
		path[i] = tmp;
	}
}

void	parse_path(t_data *data)
{
	t_envlist	*curr_env_node;

	free_path(data);
	if (!data->env)
		return ;
	while (data->env->prev)
		data->env = data->env->prev;
	curr_env_node = data->env;
	while (curr_env_node)
	{
		if (!ft_strncmp(curr_env_node->name, "PATH", 5))
		{
			data->path = ft_split(curr_env_node->value, ':');
			break ;
		}
		curr_env_node = curr_env_node->next;
	}
	if (data->path)
		add_slash(data->path);
}

void	free_path(t_data *data)
{
	int	i;

	i = -1;
	if (!data->path)
		return ;
	while (data->path[++i])
		ft_free(&data->path[i]);
	free(data->path);
	data->path = NULL;
}
