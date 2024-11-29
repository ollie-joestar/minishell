/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:25:45 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/30 00:17:31 by hanjkim          ###   ########.fr       */
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
	t_token *current;
	t_token *next;

	if (!data->token)
		return ;
	while (data->token != NULL && data->token->prev != NULL)
		data->token = data->token->prev;
	current = data->token;
	while (current != NULL)
	{
		next = current->next;
		if (current->word != NULL)
			free(current->word);
		free(current);
		current = next;
	}
	data->token = NULL;
}

void	free_old_token(t_token *token)
{
	if (!token)
		return;
	if (token->word)
		ft_free(&token->word);
	free(token);
}
void	free_token_node(t_token **token)
{
	if (token == NULL || *token == NULL)
		return ;
	if ((*token)->prev)
		(*token)->prev->next = (*token)->next;
	if ((*token)->next)
		(*token)->next->prev = (*token)->prev;
	if ((*token)->word)
		ft_free(&(*token)->word);
	free(*token);
	*token = NULL;
}
