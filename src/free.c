/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:25:45 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/14 11:37:33 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_free(&arr[i]);
		i++;
	}
	free(arr);
}

void	free_env_list(t_data *data)
{
	t_envlist	*tmp;

	if (!data->env)
		return ;
	while (data->env->prev)
		data->env = data->env->prev;
	while (data->env)
	{
		tmp = data->env;
		data->env = data->env->next;
		ft_free(&tmp->name);
		ft_free(&tmp->value);
		free(tmp);
		tmp = NULL;
	}
}

void	free_tokens(t_data *data)
{
	t_lex_token	*tmp;

	if (!data->token)
		return ;
	while (data->token->left)
		data->token = data->token->left;
	while (data->token)
	{
		tmp = data->token;
		data->token = data->token->right;
		ft_free(&tmp->word);
		free(tmp);
		tmp = NULL;
	}
}
