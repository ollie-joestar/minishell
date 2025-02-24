/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:49:00 by oohnivch          #+#    #+#             */
/*   Updated: 2025/02/24 15:34:19 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_error(char *path)
{
	char	*tmp;

	if (!path)
		return ;
	tmp = ft_strjoin("getcwd: ", "cannot access parent directories");
	if (!ft_strncmp(path, "..", 3) || !ft_strncmp(path, ".", 2))
		mspec2(tmp, "No such file or directory\n");
	ft_free(&tmp);
}

char	*get_home(t_data *data)
{
	t_envlist	*env;

	while (data->env && data->env->prev)
		data->env = data->env->prev;
	env = data->env;
	while (env)
	{
		if (!ft_strncmp(env->name, "HOME", 5))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	cd_home(t_data *data, t_exec *exec)
{
	char	*path;

	(void)exec;
	path = get_home(data);
	if (!path)
	{
		mspec("cd: HOME not set\n");
		data->status = EXIT_FAILURE;
		return ;
	}
	if (chdir(path) == -1)
	{
		mspe2("cd :", path);
		data->status = EXIT_FAILURE;
		return ;
	}
	data->status = EXIT_SUCCESS;
	if (!update_pwd(data))
		pwd_error(path);
}

char	*cd_special_path_check(t_data *data, char *path)
{
	char		*home;
	char		*tmp;
	t_envlist	*env;

	if (!ft_strncmp(path, "~", 2))
		return (ft_strdup(get_home(data)));
	else if (!ft_strncmp(path, "~/", 3))
	{
		home = get_home(data);
		tmp = ft_strjoin(home, path + 1);
		return (tmp);
	}
	else if (!ft_strncmp(path, "-", 2))
	{
		env = find_env(data->env, "OLDPWD");
		if (!env)
		{
			mspec("cd: OLDPWD not set\n");
			data->status = EXIT_FAILURE;
			return (NULL);
		}
		return (ft_strdup(env->value));
	}
	else
		return (ft_strdup(path));
}

void	failed_cd(t_data *data, char *path)
{
	char	*tmp;
	struct stat file_stat;
	
	tmp = ft_strjoin("cd: ", path);
	if (access(path, F_OK) == 0)
	{
		if (stat(path, &file_stat) == 0)
		{
			if (S_ISDIR(file_stat.st_mode))
				mspec2(tmp, "Permission denied\n");
			else
				mspec2(tmp, "Not a directory\n");
		}
	}
	else
		mspec2(tmp, "No such file or directory\n");
	data->status = 1;
	ft_free(&tmp);
}

void	cd(t_data *data, t_exec *exec)
{
	char	*path;

	path = NULL;
	if (ft_arrlen(exec->av) > 2)
		(mspec("cd: too many arguments\n"), data->status = 1);
	else if (ft_arrlen(exec->av) == 2)
	{
		path = cd_special_path_check(data, exec->av[1]);
		if (!path)
			return ;
		if (chdir(path) == -1)
			(failed_cd(data, path), ft_free(&path));
		else if (!ft_strncmp(exec->av[1], "-", 2))
			(ft_printf("%s\n", get_oldpwd(data)->value), data->status = 0);
		else
			data->status = 0;
	}
	else
		return (cd_home(data, exec));
	if (!update_pwd(data))
		pwd_error(exec->av[1]);
	ft_free(&path);
}
