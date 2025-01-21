/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:56:43 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/21 12:57:31 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlist	*get_oldpwd(t_data *data)
{
	t_envlist	*env;

	while (data->env->prev)
		data->env = data->env->prev;
	env = data->env;
	while (env)
	{
		if (!ft_strncmp(env->name, "OLDPWD", 7))
			return (env);
		env = env->next;
	}
	env = ft_calloc(1, sizeof(t_envlist));
	if (!env)
		bruh(data, "Malloc failed in get_oldpwd", 69);
	env->name = ft_strdup("OLDPWD");
	env->value = ft_strdup("");
	if (!env->name || !env->value)
		bruh(data, "Malloc failed in get_oldpwd", 69);
	while (data->env->next)
		data->env = data->env->next;
	return (env->prev = data->env, data->env->next = env, env);
}

t_envlist	*get_pwd(t_data *data)
{
	t_envlist	*env;

	while (data->env->prev)
		data->env = data->env->prev;
	env = data->env;
	while (env)
	{
		if (!ft_strncmp(env->name, "PWD", 4))
			return (env);
		env = env->next;
	}
	env = ft_calloc(1, sizeof(t_envlist));
	if (!env)
		bruh(data, "Malloc failed in get_pwd", 69);
	env->name = ft_strdup("PWD");
	env->value = ft_strdup("");
	if (!env->name || !env->value)
		bruh(data, "Malloc failed in get_pwd", 69);
	while (data->env->next)
		data->env = data->env->next;
	return (env->prev = data->env, data->env->next = env, env);
}

void	update_pwd(t_data *data)
{
	t_envlist	*env;
	t_envlist	*oldpwd;
	t_envlist	*pwd;
	char		*cwd;

	//	Maybe this will be useful later
	if (data->status != 0)
		return ;
	while (data->env->prev)
		data->env = data->env->prev;
	env = data->env;
	oldpwd = get_oldpwd(data);
	pwd = get_pwd(data);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_printerr("minishell: pwd: error retrieving current directory\n");
		data->status = 1;
		return ;
	}
	ft_free(&oldpwd->value);
	oldpwd->value = pwd->value;
	pwd->value = cwd;
}

void	pwd(t_data *data, t_exec *exec)
{
	char	*pwd;

	(void)exec;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_printerr("minishell: pwd: error retrieving current directory\n");
		data->status = 69;
		return ;
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
	ft_free(&pwd);
	data->status = 0;
}
