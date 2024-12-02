/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:37:58 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/27 14:31:54 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_is_in_env(t_data *data, char *name)
{
	t_envlist	*env;

	if (!name || !*name)
		return (0);
	while (data->env->prev)
		data->env = data->env->prev;
	env = data->env;
	while (env)
	{
		if (ft_strncmp(env->name, name, ft_strlen(env->name) + 1) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

void	delete_var_from_environment(t_data *data, char *name)
{
	t_envlist	*env;

	if (!name)
		return ;
	while (data->env->prev)
		data->env = data->env->prev;
	env = data->env;
	while (env)
	{
		if (!ft_strncmp(env->name, name, ft_strlen(env->name) + 1))
		{
			if (env->prev)
				env->prev->next = env->next;
			if (env->next)
				env->next->prev = env->prev;
			free_env_node(env);
			break ;
		}
		env = env->next;
	}
}

void	unset(t_data *data, t_exec *exec)
{
	int	i;

	i = 0;
	if (exec->av[1] == NULL)
	{
		ft_putstr_fd("unset: not enough arguments\n", 2);
		data->status = 1;
		return ;
	}
	while (exec->av[++i])
	{
		if (ft_strchr(exec->av[i], '='))
			continue ;
		if (var_is_in_env(data, exec->av[i]))
			delete_var_from_environment(data, exec->av[i]);
	}
}
