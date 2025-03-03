/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:32:11 by oohnivch          #+#    #+#             */
/*   Updated: 2025/03/03 10:30:08 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_path(t_data *data, t_exec *exec)
{
	char	*tmp;
	int		i;

	i = -1;
	if (!*exec->cmd)
		return ;
	while (data->path && *data->path && data->path[++i])
	{
		tmp = ft_strjoin(data->path[i], exec->cmd);
		if (!tmp)
			bruh(data, "Failed to allocate memory for path", 69);
		if (access(tmp, X_OK) == 0)
		{
			ft_free(&exec->cmd);
			exec->cmd = tmp;
			return ;
		}
		if (access(tmp, F_OK) == 0)
		{
			ft_free(&exec->cmd);
			exec->cmd = ft_strdup(tmp);
		}
		ft_free(&tmp);
	}
}

void	set_cmd_path(t_data *data, t_exec *exec)
{
	if (!exec->cmd)
	{
		mspec("No command to set path cmd_path.c:45\n");
		return ;
	}
	if (ft_strchr(exec->cmd, '/') || !ft_strncmp(exec->cmd, ".", 2)
		|| !ft_strncmp(exec->cmd, "..", 3))
		return ;
	if (!data->path || !*data->path)
		return ;
	set_path(data, exec);
}
