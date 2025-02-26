/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:32:53 by oohnivch          #+#    #+#             */
/*   Updated: 2025/02/26 18:59:27 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_name_value(char *av, char **new_name, char **new_value)
{
	if (ft_strchr(av, '='))
	{
		*new_name = ft_substr(av, 0, ft_strchr(av, '=') - av);
		*new_value = ft_strdup(ft_strchr(av, '=') + 1);
	}
	else
	{
		*new_name = ft_strdup(av);
		*new_value = ft_strdup("");
	}
}

static void	process_export(t_data *data, t_exec *exec, int j)
{
	t_envlist	*list;
	char		*new_name;
	char		*new_value;

	set_name_value(exec->av[j], &new_name, &new_value);
	list = find_env(data->env, new_name);
	if (list && ft_strchr(exec->av[j], '='))
		(ft_free(&list->value), list->value = ft_strdup(new_value));
	else if (ft_strchr(exec->av[j], '='))
	{
		list = create_env(new_name, new_value);
		(ft_free(&new_name), ft_free(&new_value));
		if (!list)
			bruh(data, "Memory allocation failed:export.c:102", 69);
		add_env(data->env, list);
	}
	(ft_free(&new_name), ft_free(&new_value));
}

static int	export_check(char *argv, t_data *data)
{
	int		i;
	char	*s1;
	char	*s2;

	i = 1;
	if (*argv && (!ft_isalpha(*argv) && *argv != '_'))
	{
		data->status = 1;
		s1 = ft_strjoin("`", argv);
		s2 = ft_strjoin(s1, "': not a valid identifier\n");
		return ((mspec2("export", s2), ft_free(&s2), ft_free(&s1)), 0);
	}
	while (argv[i] && argv[i] != '=')
	{
		if (!ft_isalnum(argv[i]) && argv[i] != '_')
		{
			data->status = 1;
			s1 = ft_strjoin("`", argv);
			s2 = ft_strjoin(s1, "': not a valid identifier\n");
			return ((mspec2("export", s2), ft_free(&s2), ft_free(&s1)), 0);
		}
		i++;
	}
	return (1);
}

void	export(t_data *data, t_exec *exec)
{
	int	i;

	if (ft_arrlen(exec->av) == 1)
		return (print_export(data));
	i = 0;
	while (exec->av[++i])
	{
		if (!export_check(exec->av[i], data))
			return ;
		process_export(data, exec, i);
	}
}
