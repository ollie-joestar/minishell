/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:19:32 by oohnivch          #+#    #+#             */
/*   Updated: 2025/03/03 10:55:17 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	l_max_compare(char *str, int f)
{
	if (ft_strlen(str) < 19)
		return (0);
	if (f)
	{
		if (ft_strncmp(str, L_MIN_ABS, 19) > 0)
			return (1);
	}
	else
	{
		if (ft_strncmp(str, L_MAX_ABS, 19) > 0)
			return (1);
	}
	return (0);
}

static void	numeric_long_check(t_data *data, char *str)
{
	int		i;
	int		f;
	char	*trimmed;

	i = 0;
	trimmed = ft_strtrim(str, " \t\n\v\f\r");
	if (!trimmed)
		bruh(data, "Malloc fail in exit.c:numeric_long_check", 69);
	if (ft_strlen(trimmed) < 19)
	{
		ft_free(&trimmed);
		return ;
	}
	f = trimmed[0] == '-';
	while (trimmed[i + f] == '0')
		i++;
	if (ft_strlen(trimmed + i + f) > 19 || l_max_compare(trimmed + i + f, f))
	{
		ft_free(&trimmed);
		if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
			ft_putstr_fd("exit\n", 2);
		mspec3("exit", str, "numeric argument required\n");
		bruh(data, NULL, 2);
	}
	ft_free(&trimmed);
}

static void	numeric_check(t_data *data, char *s)
{
	size_t	i;
	char	*trimmed;

	if (!*s)
	{
		if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
			ft_putstr_fd("exit\n", 2);
		(mspec3("exit", s, "numeric argument required\n"), bruh(data, NULL, 2));
	}
	trimmed = ft_strtrim(s, " \t\n\v\f\r");
	if (!trimmed)
		bruh(data, "Malloc fail in exit.c:numeric_check", 69);
	i = trimmed[0] == '-' || trimmed[0] == '+';
	while (trimmed[i] && i < ft_strlen(trimmed))
	{
		if (!ft_isdigit(trimmed[i++]))
		{
			if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
				ft_putstr_fd("exit\n", 2);
			ft_free(&trimmed);
			mspec3("exit", s, "numeric argument required\n");
			bruh(data, NULL, 2);
		}
	}
	(ft_free(&trimmed), numeric_long_check(data, s));
}

void	ft_exit(t_data *data, t_exec *exec)
{
	char	*tmp;

	restore_stds(data, exec);
	if (exec->av && exec->av[1])
	{
		numeric_check(data, exec->av[1]);
		if (exec->av[2])
		{
			data->status = 1;
			if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
			{
				tmp = join2("exit\n", "minishell: exit: too many arguments\n");
				if (!tmp)
					bruh(data, "Malloc fail in exit.c:105", 69);
				(ft_putstr_fd(tmp, 2), ft_free(&tmp));
				return ;
			}
			else
				bruh(data, "minishell: exit: too many arguments", 1);
		}
		data->status = ft_atoi(exec->av[1]) % 256;
	}
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		bruh(data, "exit", data->status);
	bruh(data, NULL, data->status);
}
