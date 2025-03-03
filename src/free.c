/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:37:22 by oohnivch          #+#    #+#             */
/*   Updated: 2025/03/03 16:37:23 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_av_list(t_exec *exec)
{
	t_avlist	*tmp;

	if (!exec->av_list)
	{
		ft_printerr("No av_list to free\n");
		return ;
	}
	while (exec->av_list && exec->av_list->prev)
		exec->av_list = exec->av_list->prev;
	while (exec->av_list)
	{
		tmp = exec->av_list;
		exec->av_list = exec->av_list->next;
		ft_free(&tmp->arg);
		free(tmp);
		tmp = NULL;
	}
}

void	free_arr(char ***arr)
{
	int	i;

	i = 0;
	if (!arr || !*arr)
		return ;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}

void	free_env_list(t_envlist *env)
{
	t_envlist	*tmp;

	if (!env)
		return ;
	while (env->prev)
		env = env->prev;
	while (env)
	{
		tmp = env;
		env = env->next;
		ft_free(&tmp->name);
		ft_free(&tmp->value);
		free(tmp);
		tmp = NULL;
	}
}
