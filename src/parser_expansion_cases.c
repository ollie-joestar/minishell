/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expansion_cases.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 22:44:16 by hanjkim           #+#    #+#             */
/*   Updated: 2025/02/27 16:16:56 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Dollar expansion cases
int	handle_dollar_exp(t_data *data, t_exp *exp)
{
	char	*exit_status_str;
	size_t	len;

	exit_status_str = ft_itoa(data->status);
	if (!exit_status_str)
		return (ft_free(&exp->result), 1);
	len = ft_strlen(exit_status_str);
	if (resize_result(exp, exp->index_res + len))
		return (ft_free(&exit_status_str), 1);
	ft_memcpy(&(exp->result[exp->index_res]), exit_status_str, len);
	exp->index_res += len;
	ft_free(&exit_status_str);
	return (0);
}

// Variable expansion cases (what a mess)
int	handle_variable_exp(t_data *data, char *word, t_exp *exp)
{
	char	*var_name;
	char	*var_value;
	size_t	name_length;
	size_t	start;
	size_t	len;

	start = exp->index_word;
	while (word[exp->index_word] != '\0'
		&& (ft_isalnum(word[exp->index_word])
			|| word[exp->index_word] == '_'))
		exp->index_word++;
	name_length = exp->index_word - start;
	var_name = ft_calloc(name_length + 1, sizeof(char));
	if (!var_name)
		return (ft_free(&exp->result), 1);
	ft_strlcpy(var_name, word + start, name_length + 1);
	var_value = get_env_value(data, var_name);
	len = ft_strlen(var_value);
	if (resize_result(exp, exp->index_res + len))
		return (ft_free(&var_name), 1);
	ft_memcpy(&(exp->result[exp->index_res]), var_value, len);
	exp->index_res += len;
	ft_free(&var_name);
	return (0);
}

// Append every character to the result string
int	handle_normal_chars(char c, t_exp *exp)
{
	resize_result(exp, exp->index_res + 1);
	exp->result[exp->index_res] = c;
	exp->index_res++;
	return (0);
}

// Process environment variables
int	process_dollar_value(t_data *data, char *word, t_exp *exp)
{
	if (word[exp->index_word] == '\0')
		handle_normal_chars('$', exp);
	else if (word[exp->index_word] == '?')
	{
		exp->index_word++;
		if (handle_dollar_exp(data, exp))
			return (1);
	}
	else if (ft_isalpha(word[exp->index_word])
		|| word[exp->index_word] == '_')
	{
		if (handle_variable_exp(data, word, exp))
			return (1);
	}
	else
		handle_normal_chars('$', exp);
	return (0);
}
