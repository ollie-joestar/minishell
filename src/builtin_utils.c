/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:15:50 by oohnivch          #+#    #+#             */
/*   Updated: 2025/02/26 15:48:31 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	store_stds(t_exec *exec)
{
	exec->stds[RD] = dup(STDIN_FILENO);
	exec->stds[WR] = dup(STDOUT_FILENO);
	exec->needs_restore = 1;
}

void	safe_print_export(t_data *data, char *name, char *value)
{
	char	*tmp;
	char	*tmp2;

	tmp = join2("declare -x ", name);
	if (!tmp)
		bruh(data, "Failed to allocate memory for export\n", 1);
	tmp2 = join2(tmp, "=\"");
	ft_free(&tmp);
	if (!tmp2)
		bruh(data, "Failed to allocate memory for export\n", 1);
	tmp = join2(tmp2, value);
	ft_free(&tmp2);
	if (!tmp)
		bruh(data, "Failed to allocate memory for export\n", 1);
	tmp2 = join2(tmp, "\"\n");
	ft_free(&tmp);
	if (!tmp2)
		bruh(data, "Failed to allocate memory for export\n", 1);
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

void	safe_print(char *str)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGPIPE, &sa, NULL);
	ft_putstr(str);
	sigaction(SIGPIPE, NULL, NULL);
}
