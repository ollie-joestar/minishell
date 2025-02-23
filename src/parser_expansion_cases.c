/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expansion_cases.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 22:44:16 by hanjkim           #+#    #+#             */
/*   Updated: 2025/02/23 20:13:51 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_dollar_exp(t_data *data, t_expander *expander)
{
	char	*exit_status_str;
	size_t	len;

	exit_status_str = ft_itoa(data->status);
	if (!exit_status_str)
		return (ft_free(&expander->result), 1);
	len = ft_strlen(exit_status_str);
	resize_result(expander, expander->index_res + len);
	ft_memcpy(&(expander->result[expander->index_res]), exit_status_str, len);
	expander->index_res += len;
	ft_free(&exit_status_str);
	return (0);
}

int	handle_variable_exp(t_data *data, char *word, t_expander *expander)
{
	char	*var_name;
	char	*var_value;
	size_t	name_length;
	size_t	start;
	size_t	len;

	start = expander->index_word;
	while (word[expander->index_word] != '\0'
		&& (ft_isalnum(word[expander->index_word])
		|| word[expander->index_word] == '_'))
		expander->index_word++;
	name_length = expander->index_word - start;
	var_name = ft_calloc(name_length + 1, sizeof(char));
	if (!var_name)
		return (ft_free(&expander->result), 1);
	ft_strlcpy(var_name, word + start, name_length + 1);
	var_value = get_env_value(data, var_name);
	len = ft_strlen(var_value);
	resize_result(expander, expander->index_res + len);
	ft_memcpy(&(expander->result[expander->index_res]), var_value, len);
	expander->index_res += len;
	ft_free(&var_name);
	return (0);
}

int	handle_normal_chars(char c, t_expander *expander)
{
	resize_result(expander, expander->index_res + 1);
	expander->result[expander->index_res] = c;
	expander->index_res++;
	return (0);
}

int	process_dollar_value(t_data *data, char *word, t_expander *expander)
{
	if (word[expander->index_word] == '\0')
		handle_normal_chars('$', expander);
	else if (word[expander->index_word] == '?')
	{
		expander->index_word++;
		handle_dollar_exp(data, expander);
	}
	else if (ft_isalpha(word[expander->index_word])
		|| word[expander->index_word] == '_')
		handle_variable_exp(data, word, expander);
	else
		handle_normal_chars('$', expander);
	return (0);
}
