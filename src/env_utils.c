/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:17:06 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/13 13:58:35 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_list(t_data *data)
{
	t_envlist	*tmp;

	if (!data->env)
		return ;
	while (data->env->prev)
		data->env = data->env->prev;
	while (data->env)
	{
		tmp = data->env;
		data->env = data->env->next;
		ft_free(&tmp->name);
		ft_free(&tmp->value);
		free(tmp);
		tmp = NULL;
	}
}

size_t	env_len(t_envlist *env)
{
	size_t	len;

	len = 0;
	if (!env)
		return (0);
	while (env->prev)
		env = env->prev;
	while (env)
	{
		len++;
		env = env->next;
	}
	return (len);
}
