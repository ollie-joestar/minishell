/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:39:11 by oohnivch          #+#    #+#             */
/*   Updated: 2024/12/02 16:53:58 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FIX THIS SHIT
static void	add_slash(t_data *data, char **path)
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
			bruh(data, "Failed alloc at add slash\n", 1);
		ft_free(&path[i]);
		path[i] = tmp;
	}
}

void	parse_path(t_data *data)
{
	t_envlist	*curr_env_node;

//	free_path(data);
	if (!data->env)
		return ;
	if (data->path)
		free_arr(&data->path);
	while (data->env->prev)
		data->env = data->env->prev;
	curr_env_node = data->env;
	while (curr_env_node)
	{
		if (!ft_strncmp(curr_env_node->name, "PATH", 5))
		{
			data->path = ft_split(curr_env_node->value, ':');
			if (!data->path)
				bruh(data, "Failed to split path", 1);
			break ;
		}
		curr_env_node = curr_env_node->next;
	}
	if (data->path)
		add_slash(data, data->path);
}
