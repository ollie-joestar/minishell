/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:32:53 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/27 14:20:05 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_export(t_data *data)
{
	t_envlist	*list;

	list = dup_env(data->env);
	if (!list)
		bruh(data, "Memory allocation failed", 1);
	sort_env(list);
	while (list->prev)
		list = list->prev;
	while (list)
	{
		if (ft_strncmp(list->name, "_", 2))
			ft_printf("declare -x %s=\"%s\"\n", list->name, list->value);
		list = list->next;	
	}
	free_env_list(list);
}

void	export(t_data *data, t_exec *exec)
{
	if (ft_arrlen(exec->av) == 1)
		return (print_export(data));
	if (!ft_isalpha(exec->av[1][0]) && exec->av[1][0] != '_')
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(exec->av[1], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		data->status = 1;
		return ;
	}
}
