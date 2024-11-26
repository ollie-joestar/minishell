/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:32:53 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/26 13:51:16 by oohnivch         ###   ########.fr       */
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
	{
		print_export(data);
	}
}
