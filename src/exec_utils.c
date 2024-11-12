/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:49:02 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/12 16:03:59 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_stds(int	stdin_copy, int	stdout_copy)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);
}


int	fork1(t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		bruh(data, "fork failed\n", 1);
	return (pid);
}
/*void	cd(t_data *data)*/
/*{*/
/*	if (!data->exec->av[1])*/
/*		data->exec->av[1] = ft_strdup("$HOME");*/
/*	if (chdir(data->exec->av[1]) < 0)*/
/*	{*/
/*		ft_putstr_fd("cd: ", 2);*/
/*		ft_putstr_fd(data->exec->av[1], 2);*/
/*		bruh(data, ": no such file or directory\n", 1);*/
/*	}*/
/*}*/
/**/
/*void	echo(t_data *data)*/
/*{*/
/*	int	i;*/
/**/
/*	i = 1;*/
/*	reroute(data);*/
/*	while (data->exec->av[i])*/
/*	{*/
/*		ft_putstr(data->exec->av[i]);*/
/*		if (data->exec->av[i + 1])*/
/*			ft_putstr(" ");*/
/*		i++;*/
/*	}*/
/*	ft_putstr("\n");*/
/*}*/
