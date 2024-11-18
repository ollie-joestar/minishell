/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:49:00 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/18 10:37:03 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home(t_data *data)
{
	t_envlist	*env;

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
		ft_putstr_fd("minishell: cd: HOME not set", 2);
		data->status = EXIT_FAILURE;
		return ;
	}
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		perror(path);
		data->status = EXIT_FAILURE;
	}
}

char	*cd_special_path_check(t_data *data, char *path)
{
	char	*home;
	char	*tmp;

	if (!ft_strncmp(path, "~", 2))
		return (get_home(data));
	else if (!ft_strncmp(path, "~/", 3))
	{
		home = get_home(data);
		tmp = ft_strjoin(home, path + 1);
		return (tmp);
	}
	else if (!ft_strncmp(path, "-", 2))
		return (get_oldpwd(data)->value);
	else
		return (path);
}

void	cd(t_data *data, t_exec *exec)
{
	char	*path;

	if (ft_arrlen(exec->av) > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments", 2);
		data->status = 1;
		return ;
	}
	else if (ft_arrlen(exec->av) == 2)
	{
		path = cd_special_path_check(data, exec->av[1]);
		if (chdir(path) == -1)
		{
			ft_putstr_fd("minishell: cd: no such file of directory", 2);
			ft_putstr_fd(path, 2);
			data->status = EXIT_FAILURE;
			return ;
		}
	}
	else
		cd_home(data, exec);
	if (data->status == EXIT_SUCCESS)
		update_pwd(data);
}

/*int	valid_dotdot_path(char *path)*/
/*{*/
/*	while (*path)*/
/*	{*/
/*		if (!ft_strncmp(path, "../", 3))*/
/*			path += 3;*/
/*		else if (!ft_strncmp(path, "..", 3) || !ft_strncmp(path, "./", 2))*/
/*			path += 2;*/
/*		else if (!ft_strncmp(path, ".", 2))*/
/*			path += 1;*/
/*		else*/
/*			return (false);*/
/*	}*/
/*	return (true);*/
/*}*/

/*bool	too_many_arguments(t_var *var, t_node *cmd)*/
/*{*/
/*	if (cmd->content[1] && cmd->content[2])*/
/*	{*/
/*		error_msg(var, ": too many arguments", 1);*/
/*		return (true);*/
/*	}*/
/*	return (false);*/
/*}*/
/**/
/*void	cd_dotdot(t_var *var, char *path)*/
/*{*/
/*	char	*rv_path;*/
/*	char	*cwd;*/
/**/
/*	if (var->cwd && var->cwd[ft_strlen(var->cwd) - 1] == '/')*/
/*		rv_path = ft_strjoin_nofree(var->cwd, path);*/
/*	else*/
/*		rv_path = ft_strjoin_three(var->cwd, path, '/');*/
/*	if (!rv_path)*/
/*		return (perror("cd"), status_1(var));*/
/*	free(var->cwd);*/
/*	chdir(path);*/
/*	cwd = getcwd(NULL, 0);*/
/*	if (!cwd)*/
/*	{*/
/*		ft_putstr_fd("cd: error retrieving current directory:", STDERR_FILENO);*/
/*		perror(" getcwd: cannot access parent directories");*/
/*		var->cwd = rv_path;*/
/*	}*/
/*	else*/
/*	{*/
/*		var->cwd = cwd;*/
/*		free(rv_path);*/
/*	}*/
/*	update_env_after_cd(var, "OLDPWD=", NEED ENV HERE);*/
/*	update_env_after_cd(var, "PWD=", var->cwd);*/
/*}*/
/**/
/*void	command_cd(t_var *var, char *path)*/
/*{*/
/*	if (!path)*/
/*		return (cd_home(var, path));*/
/*	if (valid_dotdot_path(path))*/
/*		return (cd_dotdot(var, path));*/
/*	if (chdir(path) == -1)*/
/*	{*/
/*		ft_putstr_fd("cd: ", STDERR_FILENO);*/
/*		perror(path);*/
/*		return (status_1(var));*/
/*	}*/
/*	update_env_after_cd(var, "OLDPWD=", NEED ENV HERE);*/
/*	free(var->cwd);*/
/*	var->cwd = getcwd(NULL, 0);*/
/*	if (var->cwd)*/
/*		update_env_after_cd(var, "PWD=", var->cwd);*/
/*	var->status = EXIT_SUCCESS;*/
/*}*/
/**/
