/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:41:38 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/18 10:42:25 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand(t_data *data, char *name)
{
	t_envlist	*env;

	while (data->env->prev)
		data->env = data->env->prev;
	env = data->env;
	while (env)
	{
		if (ft_strncmp(env->name, name, ft_strlen(env->name) + 1) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

/*char	expand(t_data *data, t_token *token)*/
/*{*/
/*	t_envlist	*env;*/
/*	t_token	*tmp_token;*/
/*	char		*expanded;*/
/**/
/*	expanded = NULL;*/
/*	tmp_token = token;*/
/*	env = data->env;*/
/*	while (env)*/
/*	{*/
/*		if (ft_strncmp(env->name, tmp_token->word + 1, ft_strlen(env->name) + 1) == 0)*/
/*		{*/
/*			tmp_token->word = ft_strdup(env->value);*/
/*			return ;*/
/*		}*/
/*		env = env->next;*/
/*	}*/
/*}*/
