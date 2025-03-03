/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:32:53 by oohnivch          #+#    #+#             */
/*   Updated: 2025/03/03 12:45:42 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fail_export(t_data *data, char *arg)
{
	char	*tmp1;
	char	*tmp2;

	data->status = 1;
	tmp1 = join2("export: `", arg);
	if (!tmp1)
		bruh(data, "Failed malloc in fail_export", 69);
	tmp2 = join2(tmp1, "': not a valid identifier\n");
	if (!tmp2)
		(ft_free(&tmp1), bruh(data, "Failed malloc in fail_export", 69));
	mspec(tmp2);
	ft_free(&tmp1);
	ft_free(&tmp2);
	return (0);
}

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
		*new_value = NULL;
	}
}

static void	process_export(t_data *data, t_exec *exec, int j)
{
	t_envlist	*list;
	char		*new_name;
	char		*new_value;

	set_name_value(exec->av[j], &new_name, &new_value);
	if (!new_name)
		bruh(data, "Malloc failed:export.c:55", 69);
	list = find_env(data->env, new_name);
	if (!new_value && ft_strchr(exec->av[j], '='))
		bruh(data, "Malloc failed:export.c:57", 69);
	if (list && ft_strchr(exec->av[j], '='))
		(ft_free(&list->value), list->value = ft_strdup(new_value));
	else if (!list)
	{
		list = create_env(new_name, new_value);
		(ft_free(&new_name), ft_free(&new_value));
		if (!list)
			bruh(data, "Malloc failed:export.c:69", 69);
		add_env(data->env, list);
	}
	(ft_free(&new_name), ft_free(&new_value));
}

static int	export_check(char *arg, t_data *data)
{
	int		i;

	i = 1;
	if (*arg && (!ft_isalpha(*arg) && *arg != '_'))
	{
		return (fail_export(data, arg));
	}
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (fail_export(data, arg));
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
