/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:25:45 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/27 14:14:51 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arr(char ***arr)
{
	int	i;

	i = 0;
	if (!arr || !*arr)
		return ;
	while ((*arr)[i])
	{
		/*ft_printf("freeing string [%d] \"%s\"\n", i, (*arr)[i]);*/
		free((*arr)[i]);
		(*arr)[i] = NULL;
		/*ft_printf("freed %s\n", (*arr)[i]);*/
		i++;
	}
	/*ft_printf("freeing arr\n");*/
	free(*arr);
	*arr = NULL;
	/*ft_printf("freed arr\n");*/
}

void	free_env_list(t_envlist *env)
{
	t_envlist	*tmp;

	if (!env)
		return ;
	while (env->prev)
		env = env->prev;
	while (env)
	{
		tmp = env;
		env = env->next;
		ft_free(&tmp->name);
		ft_free(&tmp->value);
		free(tmp);
		tmp = NULL;
	}
}

void	free_tokens(t_data *data)
{
	t_token	*tmp;

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

void	free_env_node(t_envlist *env)
{
	if (!env)
		return ;
	ft_free(&env->name);
	ft_free(&env->value);
	free(env);
	env = NULL;
}

// yet ANOTHER function that frees tokens
void	free_token_node(t_token **token)
{
	if ((*token)->word)
		ft_free(&(*token)->word);
	free(*token);
	*token = NULL;
}

// yet ANOTHER function that frees tokens
void	free_old_token(t_token *token)
{
	if (!token)
		return;
	ft_free(&token->word);
	ft_free((char **)&token);
}
