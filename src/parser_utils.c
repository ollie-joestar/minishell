/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 21:43:24 by hanjkim           #+#    #+#             */
/*   Updated: 2024/12/19 16:27:30 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_realloc(void *str, size_t old_size, size_t new_size)
{
	char	*new_str;

	if (new_size == 0)
		return (free(str), NULL);
	new_str = ft_calloc(new_size, sizeof(char));
	if (!new_str)
		return (NULL);
	if (str)
	{
		if (old_size > new_size)
			ft_memcpy(new_str, str, new_size);
		else
			ft_memcpy(new_str, str, old_size);
		free(str);
	}
	return (new_str);
}

char	*get_env_value(t_data *data, char *var_name)
{
	t_envlist	*current;

	if (!data || !var_name)
		return (NULL);
	current = data->env;
	while (current)
	{
		/*if (ft_strncmp(current->name, var_name, ft_strlen(var_name)) == 0)*/
		/*	return (current->value);*/
		if (ft_strlen(current->name) == ft_strlen(var_name)
			&& ft_strncmp(current->name, var_name, ft_strlen(var_name)) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int	resize_result(t_expander *expander, size_t required_size)
{
	if (required_size >= expander->result_size)
	{
		expander->old_result_size = expander->result_size;
		expander->result_size = required_size + 1;
		expander->result = ft_realloc(expander->result,
				expander->old_result_size, expander->result_size);
		if (!expander->result)
			return (-1);
	}
	return (0);
}

char	*initialize_expander(t_expander *expander, char *word)
{
	size_t	word_len;

	word_len = ft_strlen(word);
	expander->result = NULL;
	expander->result_size = 0;
	expander->old_result_size = 0;
	expander->index_word = 0;
	expander->index_res = 0;
	expander->result_size = word_len + 1;
	expander->result = ft_calloc(expander->result_size, sizeof(char));
	return (expander->result);
}
