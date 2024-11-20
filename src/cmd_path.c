/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:32:11 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/20 15:05:31 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_path(t_data *data, t_exec *exec)
{
	char	*tpm;
	int		i;

	if (!data->path || !*data->path)
	{
		ft_printf("Path not set\n");
		return ;
	}
	i = -1;
	while (data->path[++i])
	{
		tpm = ft_strjoin(data->path[i], exec->cmd);
		if (access(tpm, X_OK) == 0)
		{
			ft_printf("Found executable %s\n", tpm);
			ft_free(&exec->cmd);
			exec->cmd = tpm;
			return ;
		}
		if (access(tpm, F_OK) == 0)
		{
			ft_printf("Found file %s\n", tpm);
			ft_free(&exec->cmd);
			exec->cmd = ft_strdup(tpm);
		}
		ft_free(&tpm);
		if (!data->path[i + 1])
			break ;
	}
	/*ft_printf("Executable not found\n");*/
}

void	set_cmd_path(t_data *data, t_exec *exec)
{
	/*if (!exec->cmd)*/
	/*	exec->cmd = ft_strdup(exec->av[0]);*/
	if (ft_strchr(exec->cmd, '/'))
		return ;
	else
		set_path(data, exec);
}
