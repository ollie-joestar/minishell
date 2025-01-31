/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:37:58 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/31 18:31:36 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_var(t_envlist *node)
{
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
			remove_var(node);
		data->status = 0;
	}
}
