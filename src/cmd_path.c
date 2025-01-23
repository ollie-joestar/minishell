/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:32:11 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/23 15:28:43 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_path(t_data *data, t_exec *exec)
{
	char	*tpm;
	int		i;

	i = -1;
	while (data->path && *data->path && data->path[++i])
	{
		tpm = ft_strjoin(data->path[i], exec->cmd);
		if (access(tpm, X_OK) == 0)
		{
			ft_free(&exec->cmd);
			exec->cmd = tpm;
			return ;
		}
		if (access(tpm, F_OK) == 0)
		{
			ft_free(&exec->cmd);
			exec->cmd = ft_strdup(tpm);
		}
		ft_free(&tpm);
		if (!data->path[i + 1])
			break ;
	}
}

void	set_cmd_path(t_data *data, t_exec *exec)
{
	if (ft_strchr(exec->cmd, '/') || !ft_strncmp(exec->cmd, ".", 2))
		return ;
	if (!data->path || !*data->path)
	{
		/*requiem(1, "minishell: Path not set\n");*/
		return ;
	}
	set_path(data, exec);
}
