/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:32:11 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/14 14:37:14 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_path(t_data *data, t_exec *exec)
{
	char	*tpm;
	int		i;

	if (!data->path || !*data->path)
		return ;
	i = -1;
	while (data->path[++i])
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

void	find_cmd_path(t_data *data, t_exec *exec)
{
	exec->cmd = ft_strdup(exec->av[0]);
	if (ft_strchr(exec->cmd, '/'))
		return ;
	else
		find_path(data, exec);
}
