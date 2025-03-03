/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:35:33 by oohnivch          #+#    #+#             */
/*   Updated: 2025/03/03 16:35:36 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*echo_join(t_data *data, char **str, char *arg, char *sep)
{
	char	*tmp;

	tmp = join2(*str, arg);
	ft_free(str);
	if (!tmp)
		bruh(data, "Failed to allocate memory for echo\n", 1);
	*str = tmp;
	if (sep)
	{
		tmp = join2(*str, " ");
		ft_free(str);
		if (!tmp)
			bruh(data, "Failed to allocate memory for echo\n", 1);
		*str = tmp;
	}
	return (*str);
}

static void	echo_str_join_and_print(t_data *data, char **argv, int i, int nl)
{
	char	*str;
	char	*tmp;

	str = NULL;
	tmp = NULL;
	while (argv[i])
	{
		echo_join(data, &str, argv[i], argv[i + 1]);
		i++;
	}
	if (!nl)
	{
		tmp = join2(str, "\n");
		ft_free(&str);
		if (!tmp)
			bruh(data, "Failed to allocate memory for echo\n", 1);
		str = tmp;
	}
	if (pid(data) == 0)
		safe_print(str);
	else
		ft_putstr(str);
	ft_free(&str);
}

static int	check_n_flag(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '-')
		i++;
	else
		return (0);
	while (str[i] == 'n')
		i++;
	if (str[i] == '\0' && i > 1)
		return (1);
	return (0);
}

void	echo(t_data *data, t_exec *exec)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (ft_arrlen(exec->av) == 1)
	{
		ft_putchar('\n');
		data->status = 0;
		return ;
	}
	while (check_n_flag(exec->av[i]))
		n = i++;
	if (*(exec->av + i))
		echo_str_join_and_print(data, exec->av, i, n);
	data->status = 0;
}
