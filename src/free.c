/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:08:52 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/22 11:54:09 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_av_list(t_exec *exec)
{
	t_avlist	*tmp;

	if (!exec->av_list)
		return ;
	while (exec->av_list->prev)
		exec->av_list = exec->av_list->prev;
	while (exec->av_list)
	{
		tmp = exec->av_list;
		exec->av_list = exec->av_list->next;
		ft_free(&tmp->arg);
		free(tmp);
		tmp = NULL;
	}
}

void	free_arr(char ***arr)
{
	int	i;

	i = 0;
	if (!arr || !*arr)
		return ;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
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
	t_token	*current;
	t_token	*next;

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

void	free_env_node(t_envlist *env)
{
	if (!env)
		return ;
	ft_free(&env->name);
	ft_free(&env->value);
	free(env);
	env = NULL;
}

void	free_segment(t_segment **seg)
{
	t_segment	*next;

	while (*seg)
	{
		next = (*seg)->next;
		if ((*seg)->text)
			free((*seg)->text);
		free(*seg);
		*seg = next;
	}
}

// yet ANOTHER function that frees tokens
void	free_old_token(t_token *token)
{
	if (!token)
		return ;
	if (token->segments)
		free_segment(&token->segments);
	if (token->word)
		ft_free(&token->word);
	free(token);
	token = NULL;
}

// yet ANOTHER function that frees tokens
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
	if ((*token)->segments)
		free_segment(&(*token)->segments);
	free(*token);
	*token = NULL;
}
