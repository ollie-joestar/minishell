/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:49:02 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 15:37:13 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reset_stds(int	stdin_copy, int	stdout_copy)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);
}

void	cd(t_data *data)
{
	if (!data->exec->av[1])
		data->exec->av[1] = ft_strdup("$HOME");
	if (chdir(data->exec->av[1]) < 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(data->exec->av[1], 2);
		bruh(data, ": no such file or directory\n", 1);
	}
}

void	echo(t_data *data)
{
	int	i;

	i = 1;
	reroute(data);
	while (data->exec->av[i])
	{
		ft_putstr(data->exec->av[i]);
		if (data->exec->av[i + 1])
			ft_putstr(" ");
		i++;
	}
	ft_putstr("\n");
}

void	run_builtin(t_data *data)
{
	int	stdin_copy;
	int	stdout_copy;

	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	if (data->exec->av[0] == 0)
		bruh(data, "cmd is null\n", 1);
	if (!(ft_strncmp(data->exec->av[0], "exit", 5)))
		bruh(data, NULL, 0);
	if (!(ft_strncmp(data->exec->av[0], "cd", 3)))
		cd(data);
	if (!(ft_strncmp(data->exec->av[0], "echo", 5)))
		echo(data);
	reset_stds(stdin_copy, stdout_copy);
}

void	runcmd(t_data *data)
{
	t_exec *exec;

	exec = data->exec;
	if (exec->type == BUILTIN)
		return (run_builtin(data));
	else
		return (run_exec(data));
}
