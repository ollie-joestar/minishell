/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:02:31 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/31 19:19:07 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_underscore(t_data *data, t_envlist *list)
{
	char		*underscore;
	char		*pwd;
	t_envlist	*tmp;

	if (!list)
		return ;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		bruh(data, "Memory allocation failed", 69);
	underscore = ft_strjoin(pwd, "/./minishell");
	if (!underscore)
		bruh(data, "Memory allocation failed", 69);
	ft_free(&pwd);
	while (list && list->next)
		list = list->next;
	tmp = ft_calloc(1, sizeof(t_envlist));
	if (!tmp)
		bruh(data, "Memory allocation failed", 69);
	tmp->name = ft_strdup("_");
	tmp->value = underscore;
	if (!tmp->name || !tmp->value)
		bruh(data, "Memory allocation failed", 69);
	tmp->prev = list;
	list->next = tmp;
}

void	create_new_pwd(t_data *data, t_envlist *list)
{
	char	*pwd;

	if (!list)
		return ;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		bruh(data, "Memory allocation failed", 69);
	list->name = ft_strdup("PWD");
	list->value = pwd;
	if (!list->value || !list->name)
		bruh(data, "Memory allocation failed", 69);
}

void	shlvl(t_data *data, t_envlist *list)
{
	t_envlist	*shlvl;
	char		*value;
	int			i_value;

	shlvl = find_env(list, "SHLVL");
	if (shlvl)
	{
		value = shlvl->value;
		i_value = ft_atoi(value);
		i_value++;
		ft_free(&shlvl->value);
		value = ft_itoa(i_value);
		shlvl->value = value;
		if (!shlvl->value)
			bruh(data, "Memory allocation failed", 69);
	}
	else
		add_env(list, create_env("SHLVL", "1"));
}

t_envlist	*create_new_env(t_data *data)
{
	t_envlist	*list;

	list = ft_calloc(1, sizeof(t_envlist));
	if (!list)
		bruh(data, "Memory allocation failed", 69);
	shlvl(data, list);
	create_new_pwd(data, list);
	create_underscore(data, list);
	return (list);
}

