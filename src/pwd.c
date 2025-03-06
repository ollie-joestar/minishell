/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:42:07 by oohnivch          #+#    #+#             */
/*   Updated: 2025/03/06 16:07:14 by oohnivch         ###   ########.fr       */
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
		if (!env)
			bruh(data, "Malloc failed in get_oldpwd", 69);
		if (data->env)
			add_env(data->env, env);
		else
			data->env = env;
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
		if (!env)
			bruh(data, "Malloc failed in get_pwd", 69);
		if (data->env)
			add_env(data->env, env);
		else
			data->env = env;
	}
	return (env);
}

int	update_pwd(t_data *data, int check)
{
	t_envlist	*oldpwd;
	t_envlist	*pwd;
	char		*cwd;

	if (check == -1)
		return (1);
	while (data && data->env && data->env->prev)
		data->env = data->env->prev;
	oldpwd = get_oldpwd(data);
	pwd = get_pwd(data);
	if (!oldpwd || !pwd)
		return (0);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		mspec("cd: error retrieving current directory\n");
		data->status = 1;
		return (0);
	}
	ft_free(&oldpwd->value);
	oldpwd->value = pwd->value;
	pwd->value = cwd;
	return (1);
}

void	pwd(t_data *data, t_exec *exec)
{
	char	*pwd;
	char	*tmp;

	(void)exec;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		mspec2("pwd", "error retrieving current directory\n");
		data->status = 69;
		return ;
	}
	if (pid(data) == 0)
	{
		tmp = join2(pwd, "\n");
		safe_print(tmp);
		ft_free(&tmp);
	}
	else
		ft_putendl_fd(pwd, STDOUT_FILENO);
	ft_free(&pwd);
	data->status = 0;
}
