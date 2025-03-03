/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:41:52 by oohnivch          #+#    #+#             */
/*   Updated: 2025/03/03 16:41:52 by oohnivch         ###   ########.fr       */
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
				bruh(data, "Failed to split cmd_path.c:52", 1);
			break ;
		}
		curr_env_node = curr_env_node->next;
	}
	if (data->path)
		add_slash(data, data->path);
}

int	checkfile(char *file)
{
	char	*path_to_file;
	int		i;
	int		name_len;

	i = 1;
	name_len = ft_strlen(file) - 1;
	if (name_len <= 0)
		return (-1);
	while (file[name_len - i] != '/' && i <= name_len)
		i++;
	if (i == name_len)
		return (0);
	path_to_file = ft_substr(file, 0, name_len - i);
	if (access(path_to_file, F_OK) == 0)
	{
		if (access(path_to_file, W_OK) == -1)
		{
			ft_free(&path_to_file);
			return (-1);
		}
		ft_free(&path_to_file);
	}
	else
		return (-1);
	return (0);
}
