/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:49:02 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/12 16:18:22 by oohnivch         ###   ########.fr       */
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
