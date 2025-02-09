/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:56:43 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/31 16:19:43 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlist	*get_oldpwd(t_data *data)
{
	t_envlist	*env;

	env = find_env(data->env, "OLDPWD");
	if (!env)
	{
		env = create_env("OLDPWD", "");
		add_env(data->env, env);
	}
	return (env);
}

t_envlist	*get_pwd(t_data *data)
{
	t_envlist	*env;

	env = find_env(data->env, "PWD");
	if (!env)
	{
		env = create_env("PWD", "");
		add_env(data->env, env);
	}
	return (env);
}

void	update_pwd(t_data *data)
{
	t_envlist	*env;
	t_envlist	*oldpwd;
	t_envlist	*pwd;
	char		*cwd;

	//	Maybe this will be useful later
	/*if (data->status != 0)*/
	/*	return ;*/
	while (data->env->prev)
		data->env = data->env->prev;
	env = data->env;
	oldpwd = get_oldpwd(data);
	pwd = get_pwd(data);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		mspec("pwd: error retrieving current directory\n");
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
