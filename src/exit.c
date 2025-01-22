/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:19:32 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/22 16:27:04 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	l_max_min_compare(char *str, int f)
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
	/*ft_printf("trimmed: %s\n", trimmed);*/
	f = trimmed[0] == '-';
	while (trimmed[i + f] == '0')
		i++;
	/*ft_printf("trimmed + i + f: %s\n", trimmed + i + f);*/
	if (ft_strlen(trimmed + i + f) > 19 || l_max_min_compare(trimmed + i + f, f))
	{
		ft_free(&trimmed);
		if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
			ft_printerr("exit\n");
		requiem(3, "minishell: exit: ", str, ": numeric argument required\n");
		bruh(data, NULL, 2);
	}
	ft_free(&trimmed);
}

static void	numeric_check(t_data *data, char *str)
{
	size_t	i;
	char	*trimmed;

	if (!*str)
	{
		if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
			ft_printerr("exit\n");
		ft_printerr("minishell: exit: %s: numeric argument required\n", str);
		bruh(data, NULL, 2);
	}
	trimmed = ft_strtrim(str, " \t\n\v\f\r");
	i = trimmed[0] == '-' || trimmed[0] == '+';
	/*ft_printf("trimmed: %s\n", trimmed);*/
	/*ft_printf("trimmed + i: %s\n", trimmed + i);*/
	while (trimmed[i] && i < ft_strlen(trimmed))
	{
		if (!ft_isdigit(trimmed[i++]))
		{
			if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
				ft_printerr("exit\n");
			ft_printerr("minishell: exit: %s: numeric argument required\n", str);
			/*ft_printerr("index of problem: %d\n in string \"%s\"\n", i, trimmed);*/
			/*ft_printf("nondigit char is [%c]\n", trimmed[i]);*/
			(ft_free(&trimmed), bruh(data, NULL, 2));
		}
	}
	if (ft_strlen(trimmed) >= 19)
		(ft_free(&trimmed), numeric_long_check(data, str));
	ft_free(&trimmed);
}

void	ft_exit(t_data *data, t_exec *exec)
{
	if (exec->av && exec->av[1])
	{
		numeric_check(data, exec->av[1]);
		if (exec->av[2])
		{
			data->status = 1;
			if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
			{
				ft_printerr("exit\nminishell: exit: too many arguments\n");
				return ;
			}
			else
				bruh(data, "minishell: exit: too many arguments", 1);
		}
		data->status = ft_atoi(exec->av[1]) % 256;
		/*if (data->status < 0 || data->status > 255)*/
		/*	data->status = 69;*/
	}
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		bruh(data, "exit", data->status);
	bruh(data, NULL, data->status);
}
