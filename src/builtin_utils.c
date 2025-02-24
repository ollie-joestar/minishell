/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:15:50 by oohnivch          #+#    #+#             */
/*   Updated: 2025/02/24 17:46:07 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	store_stds(t_exec *exec)
{
	exec->stds[RD] = dup(STDIN_FILENO);
	exec->stds[WR] = dup(STDOUT_FILENO);
	exec->needs_restore = 1;
}

void	restore_stds(t_exec *exec)
{
	if (exec->needs_restore)
	{
		if (exec->stds[RD] != STDIN_FILENO)
		{
			dup2(exec->stds[RD], STDIN_FILENO);
			close(exec->stds[RD]);
		}
		if (exec->stds[WR] != STDOUT_FILENO)
		{
			dup2(exec->stds[WR], STDOUT_FILENO);
			close(exec->stds[WR]);
		}
		exec->needs_restore = 0;
	}
}
