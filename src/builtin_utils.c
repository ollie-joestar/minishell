/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:15:50 by oohnivch          #+#    #+#             */
/*   Updated: 2025/03/07 17:04:22 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	safe_print_export(t_data *data, t_envlist *l, char *n, char *v)
{
	char	*tmp;
	char	*tmp2;

	tmp = join2("declare -x ", n);
	if (!tmp)
		(free_env_list(l), bruh(data, "Failed malloc in export\n", 1));
	if (v)
	{
		tmp2 = join2(tmp, "=\"");
		ft_free(&tmp);
		if (!tmp2)
			(free_env_list(l), bruh(data, "Failed malloc in export\n", 1));
		tmp = join2(tmp2, v);
		ft_free(&tmp2);
		if (!tmp)
			(free_env_list(l), bruh(data, "Failed malloc in export\n", 1));
		tmp2 = join2(tmp, "\"\n");
	}
	else
		tmp2 = join2(tmp, "\n");
	ft_free(&tmp);
	if (!tmp2)
		(free_env_list(l), bruh(data, "Failed malloc in export\n", 1));
	safe_print(tmp2);
	ft_free(&tmp2);
}

void	safe_print_env(t_data *data, char *name, char *value)
{
	char	*tmp;
	char	*tmp2;

	tmp = join2(name, "=");
	if (!tmp)
		bruh(data, "Failed to allocate memory for env\n", 1);
	tmp2 = join2(tmp, value);
	ft_free(&tmp);
	if (!tmp2)
		bruh(data, "Failed to allocate memory for env\n", 1);
	tmp = join2(tmp2, "\n");
	ft_free(&tmp2);
	if (!tmp)
		bruh(data, "Failed to allocate memory for env\n", 1);
	safe_print(tmp);
	ft_free(&tmp);
}

void	store_stds(t_data *data, t_exec *exec)
{
	exec->stds[RD] = dup(STDIN_FILENO);
	exec->stds[WR] = dup(STDOUT_FILENO);
	if (exec->stds[RD] == -1 || exec->stds[WR] == -1)
		bruh(data, "minishell: failed to duplicate file descriptors", 1);
	exec->needs_restore = 1;
}

void	restore_stds(t_data *data, t_exec *exec)
{
	int	check;

	check = 0;
	if (exec->needs_restore)
	{
		if (exec->stds[RD] != STDIN_FILENO)
		{
			check = dup2(exec->stds[RD], STDIN_FILENO);
			close(exec->stds[RD]);
			if (check == -1)
				bruh(data, "minishell: failed to restore file descriptors", 1);
		}
		if (exec->stds[WR] != STDOUT_FILENO)
		{
			check = dup2(exec->stds[WR], STDOUT_FILENO);
			close(exec->stds[WR]);
			if (check == -1)
				bruh(data, "minishell: failed to restore file descriptors", 1);
		}
		exec->needs_restore = 0;
	}
}

void	safe_print(char *str)
{
	signal(SIGPIPE, SIG_IGN);
	ft_putstr(str);
	signal(SIGPIPE, SIG_DFL);
}
