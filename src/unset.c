/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:43:05 by oohnivch          #+#    #+#             */
/*   Updated: 2025/03/03 16:43:11 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_var(t_data *data, t_envlist *node)
{
	if (!node || !data->env)
		return ;
	if (node == data->env)
	{
		if (data->env->prev)
			data->env = data->env->prev;
		else
			data->env = data->env->next;
	}
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	ft_free(&node->name);
	ft_free(&node->value);
	free(node);
	node = NULL;
}

void	unset(t_data *data, t_exec *exec)
{
	int			i;
	t_envlist	*node;

	i = 0;
	if (!exec->av[1])
		return ;
	while (exec->av[++i])
	{
		if (ft_strchr(exec->av[i], '='))
			continue ;
		node = find_env(data->env, exec->av[i]);
		if (node)
			remove_var(data, node);
		data->status = 0;
	}
}
