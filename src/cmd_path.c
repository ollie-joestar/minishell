/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:35:18 by oohnivch          #+#    #+#             */
/*   Updated: 2025/03/06 15:29:45 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_path_process(t_data *data, t_exec *exec, int i, char **cmd)
{
	char	*check;

	check = join2(data->path[i], *cmd);
	if (!check)
		(ft_free(cmd), bruh(data, "Failed to allocate memory for path", 69));
	if (access(check, X_OK) == 0)
	{
		ft_free(&exec->cmd);
		exec->cmd = check;
		return (1);
	}
	if (access(check, F_OK) == 0)
	{
		ft_free(&exec->cmd);
		exec->cmd = check;
		return (0);
	}
	ft_free(&check);
	return (0);
}

void	set_path(t_data *data, t_exec *exec)
{
	char	*cmd;
	int		i;

	i = -1;
	if (!exec->cmd || !*exec->cmd)
		return ;
	cmd = ft_strdup(exec->cmd);
	if (!cmd)
		bruh(data, "Failed to allocate memory for path", 69);
	while (data->path && *data->path && data->path[++i])
	{
		if (set_path_process(data, exec, i, &cmd))
			break ;
	}
	ft_free(&cmd);
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
