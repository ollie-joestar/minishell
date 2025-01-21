/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:36:14 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/21 19:40:14 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checkfile(char *file)
{
	char *path_to_file;
	int	i;
	int	name_len;

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

void	bruh(t_data *data, char *s, int status)
{
	if (s)
		(ft_putstr_fd(s, 2), ft_putstr_fd("\n", 2));
	clean_exec(data);
	free_env_list(data->env);
	free_arr(&data->ev);
	free_arr(&data->path);
	ft_free(&data->line);
	free_tokens(data);
	/*clear_history();*/
	rl_clear_history();
	if (data)
		free(data);
	exit(status);
}

size_t	ft_arrlen(char **arr)
{
	size_t	i;

	if (!arr || !*arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	skip_spaces(char *input, int *i)
{
	while ((input[*i] == ' ' || input[*i] == '\t'))
		(*i)++;
}
