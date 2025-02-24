/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 21:43:24 by hanjkim           #+#    #+#             */
/*   Updated: 2025/02/24 18:46:34 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_realloc(char *str, size_t old_size, size_t new_size)
{
	char	*new_str;

	if (new_size == 0)
		return (ft_free(&str), NULL);
	new_str = ft_calloc(new_size, sizeof(char));
	if (!new_str)
		return (NULL);
	if (str)
	{
		if (old_size > new_size)
			ft_memcpy(new_str, str, new_size);
		else
			ft_memcpy(new_str, str, old_size);
		ft_free(&str);
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
		if (ft_strlen(current->name) == ft_strlen(var_name)
			&& ft_strncmp(current->name, var_name, ft_strlen(var_name)) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int	resize_result(t_exp *exp, size_t required_size)
{
	if (required_size >= exp->result_size)
	{
		exp->old_result_size = exp->result_size;
		exp->result_size = required_size + 1;
		exp->result = ft_realloc(exp->result,
				exp->old_result_size, exp->result_size);
	}
	return (0);
}

char	*initialize_expander(t_exp *exp, char *word)
{
	size_t	word_len;

	word_len = ft_strlen(word);
	exp->result = NULL;
	exp->result_size = 0;
	exp->old_result_size = 0;
	exp->index_word = 0;
	exp->index_res = 0;
	exp->result_size = word_len + 1;
	exp->result = ft_calloc(exp->result_size, sizeof(char));
	if (!exp->result)
		return (NULL);
	return (exp->result);
}
