/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:49:00 by oohnivch          #+#    #+#             */
/*   Updated: 2025/03/03 12:07:02 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_home(t_data *data)
{
	char	*path;
	int		check;

	check = 0;
	path = get_home(data);
	if (!path)
	{
		mspec("cd: HOME not set\n");
		data->status = EXIT_FAILURE;
		return ;
	}
	check = chdir(path);
	if (check == -1)
	{
		mspe2("cd :", path);
		data->status = EXIT_FAILURE;
		return ;
	}
	data->status = EXIT_SUCCESS;
	if (!update_pwd(data, check))
		pwd_error(path);
}

char	*cd_special_path_check(t_data *data, char *path)
{
	char		*home;
	char		*tmp;
	t_envlist	*env;

	if (!ft_strncmp(path, "~", 2))
		return (cd_home(data), NULL);
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
	char		*tmp;
	struct stat	file_stat;

	tmp = ft_strjoin("cd: ", path);
	if (!tmp)
		(ft_free(&path), bruh(data, "Failed malloc in failed cd\n", 1));
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

static void	print_cd_minus(t_data *data, char *path)
{
	char	*str;

	str = join2(path, "\n");
	if (pid(data) == 0)
		safe_print(str);
	else
		ft_putstr(str);
	ft_free(&str);
	data->status = 0;
}

void	cd(t_data *data, t_exec *exec)
{
	char	*path;
	int		check;

	path = NULL;
	check = 0;
	if (ft_arrlen(exec->av) > 2)
		(mspec("cd: too many arguments\n"), data->status = 1);
	else if (ft_arrlen(exec->av) == 2)
	{
		path = cd_special_path_check(data, exec->av[1]);
		if (!path)
			return ;
		check = chdir(path);
		if (check == -1)
			(failed_cd(data, path), ft_free(&path));
		else if (!ft_strncmp(exec->av[1], "-", 2))
			print_cd_minus(data, get_oldpwd(data)->value);
		else
			data->status = 0;
	}
	else
		return (cd_home(data));
	if (!update_pwd(data, check))
		pwd_error(exec->av[1]);
	ft_free(&path);
}
