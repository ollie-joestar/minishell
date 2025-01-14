/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:02:31 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/14 14:07:10 by oohnivch         ###   ########.fr       */
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

void	create_shlvl(t_data *data, t_envlist *list)
{
	if (!list)
		return ;
	list->name = ft_strdup("SHLVL");
	list->value = ft_strdup("1");
	if (!list->value || !list->name)
		bruh(data, "Memory allocation failed", 69);
}

void	update_shlvl(t_data *data, t_envlist *list)
{
	int		shlvl;

	while (list && list->prev)
		list = list->prev;
	while (list && list->next)
	{
		if (!ft_strncmp(list->name, "SHLVL", 6))
		{
			shlvl = ft_atoi(list->value) + 1;
			free(list->value);
			list->value = ft_itoa(shlvl);
			if (!list->value)
				bruh(data, "Memory allocation failed", 69);
			return ;
		}
		list = list->next;
	}
	list->next = ft_calloc(1, sizeof(t_envlist));
	if (!list->next)
		bruh(data, "Memory allocation failed", 69);
	list->next->prev = list;
	create_shlvl(data, list->next);
}

t_envlist	*create_new_env(t_data *data)
{
	t_envlist	*list;

	list = ft_calloc(1, sizeof(t_envlist));
	if (!list)
		bruh(data, "Memory allocation failed", 69);
	create_new_pwd(data, list);
	update_shlvl(data, list);
	create_underscore(data, list);
	return (list);
}

