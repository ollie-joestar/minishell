/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:02:31 by oohnivch          #+#    #+#             */
/*   Updated: 2025/02/24 16:02:11 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**/
/*void	create_underscore(t_data *data, t_envlist *list)*/
/*{*/
/*	char		*underscore;*/
/*	char		*pwd;*/
/*	t_envlist	*tmp;*/
/**/
/*	if (!list)*/
/*		return ;*/
/*	pwd = getcwd(NULL, 0);*/
/*	if (!pwd)*/
/*		bruh(data, "Memory allocation failed", 69);*/
/*	underscore = ft_strjoin(pwd, "/./minishell");*/
/*	if (!underscore)*/
/*		bruh(data, "Memory allocation failed", 69);*/
/*	ft_free(&pwd);*/
/*	while (list && list->next)*/
/*		list = list->next;*/
/*	tmp = ft_calloc(1, sizeof(t_envlist));*/
/*	if (!tmp)*/
/*		bruh(data, "Memory allocation failed", 69);*/
/*	tmp->name = ft_strdup("_");*/
/*	tmp->value = underscore;*/
/*	if (!tmp->name || !tmp->value)*/
/*		bruh(data, "Memory allocation failed", 69);*/
/*	tmp->prev = list;*/
/*	list->next = tmp;*/
/*}*/

t_envlist	*create_underscore(t_data *data)
{
	char		*underscore;
	char		*cwd;
	t_envlist	*list;

	if (!data)
		return (NULL);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		bruh(data, "Memory allocation failed", 69);
	underscore = ft_strjoin(cwd, "/./minishell");
	if (!underscore)
		bruh(data, "Memory allocation failed", 69);
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
		bruh(data, "Memory allocation failed", 69);
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
		i_value++;
		ft_free(&shlvl->value);
		new_value = ft_itoa(i_value);
		shlvl->value = new_value;
		if (!shlvl->value)
			bruh(data, "Memory allocation failed", 69);
	}
	else
	{
		shlvl = create_env("SHLVL", "1");
		add_env(list, shlvl);
	}
}

t_envlist	*create_new_env(t_data *data)
{
	t_envlist	*list;
	t_envlist	*pwd;
	t_envlist	*underscore;

	/*list = ft_calloc(1, sizeof(t_envlist));*/
	/*if (!list)*/
	/*	bruh(data, "Memory allocation failed", 69);*/

	list = create_env("SHLVL" ,"1");
	if (!list)
		bruh(data, "Memory allocation failed", 69);
	/*data->env = list;*/
	/*print_env(data);*/
	if (!find_env(list, "PWD"))
	{
		pwd = create_new_pwd(data);
		if (!pwd)
			bruh(data, "Memory allocation failed", 69);
		add_env(pwd, list);
	}
	/*data->env = list;*/
	/*print_env(data);*/
	if (!find_env(list, "_"))
	{
		underscore = create_underscore(data);
		if (!underscore)
			bruh(data, "Memory allocation failed", 69);
		add_env(list, underscore);
	}
	/*data->env = list;*/
	/*print_env(data);*/
	while (list && list->prev)
		list = list->prev;
	return (list);
}
