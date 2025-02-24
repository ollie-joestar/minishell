/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:54:18 by oohnivch          #+#    #+#             */
/*   Updated: 2025/02/24 17:57:23 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	pid(t_data *data)
{
	if (!data->pid_list)
		return (0);
	return (data->pid_list->pid);
}

// returns the last pid in the pid list
pid_t	lpid(t_data *data)
{
	t_pidlist	*tmp;

	if (!data->pid_list)
		return (0);
	tmp = data->pid_list;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp->pid);
}

void	add_pid(t_data *data, pid_t pid)
{
	t_pidlist	*new;

	new = ft_calloc(sizeof(t_pidlist), 1);
	if (!new)
		bruh(data, "Malloc failed pid.c:41\n", 1);
	new->pid = pid;
	new->next = NULL;
	if (data->pid_list)
	{
		while (data->pid_list->next)
			data->pid_list = data->pid_list->next;
		data->pid_list->next = new;
	}
	new->prev = data->pid_list;
	data->pid_list = new;
}
