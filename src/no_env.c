/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:40:13 by oohnivch          #+#    #+#             */
/*   Updated: 2025/03/06 16:27:35 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlist	*create_underscore(t_data *data)
{
	char		*underscore;
	char		*cwd;
	t_envlist	*list;

	if (!data)
		return (NULL);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		bruh(data, "Malloc failed no_env.c:25", 69);
	underscore = ft_strjoin(cwd, "/./minishell");
	if (!underscore)
		bruh(data, "Malloc failed no_env.c:28", 69);
	ft_free(&cwd);
	list = create_env("_", underscore);
	ft_free(&underscore);
	return (list);
}

t_envlist	*create_new_pwd(t_data *data)
{
	char		*cwd;
	t_envlist	*list;

	if (!data)
		return (NULL);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		bruh(data, "Malloc failed no_env.c:44", 69);
	list = create_env("PWD", cwd);
	ft_free(&cwd);
	return (list);
}

void	shlvl(t_data *data, t_envlist *list)
{
	t_envlist	*shlvl;
	char		*new_value;
	int			i_value;

	shlvl = find_env(list, "SHLVL");
	if (shlvl)
	{
		i_value = ft_atoi(shlvl->value);
		if (i_value >= 1000 || i_value < 0)
			i_value = 0;
		else
			i_value++;
		ft_free(&shlvl->value);
		new_value = ft_itoa(i_value);
		if (!new_value)
			(free_env_list(list), bruh(data, "Malloc failed no_env.c:65", 69));
		shlvl->value = new_value;
	}
	else
	{
		shlvl = create_env("SHLVL", "1");
		if (!shlvl)
			(free_env_list(list), bruh(data, "Malloc failed no_env.c:71", 69));
		add_env(list, shlvl);
	}
}

t_envlist	*create_new_env(t_data *data)
{
	t_envlist	*list;
	t_envlist	*pwd;
	t_envlist	*underscore;

	list = create_env("SHLVL", "1");
	if (!list)
		bruh(data, "Malloc failed no_env.c:82", 69);
	if (!find_env(list, "PWD"))
	{
		pwd = create_new_pwd(data);
		if (!pwd)
			(free_env_list(list), bruh(data, "Malloc failed no_env.c:87", 69));
		add_env(pwd, list);
	}
	if (!find_env(list, "_"))
	{
		underscore = create_underscore(data);
		if (!underscore)
			(free_env_list(list), bruh(data, "Malloc failed no_env.c:94", 69));
		add_env(list, underscore);
	}
	while (list && list->prev)
		list = list->prev;
	return (list);
}
