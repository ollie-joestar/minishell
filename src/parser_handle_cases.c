/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_cases.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 22:44:16 by hanjkim           #+#    #+#             */
/*   Updated: 2024/12/01 22:44:49 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_dollar_exp(t_data *data, t_expander *expander)
{
	char	*exit_status_str;
	size_t	len;

	exit_status_str = ft_itoa(data->exit_status);
	if (!exit_status_str)
		return (free(expander->result), -1);
	len = ft_strlen(exit_status_str);
	if (resize_result(expander, expander->j + len) == -1)
		return (free(exit_status_str), -1);
	ft_memcpy(&(expander->result[expander->j]), exit_status_str, len);
	expander->j += len;
	free(exit_status_str);
	return (0);
}

int	handle_variable_exp(t_data *data, char *word, t_expander *expander)
{
	char	var_name[256];
	char	*var_value;
	size_t	len;
	size_t	var_len;

	var_len = 0;
	while (word[expander->i] != '\0'
		&& (ft_isalnum(word[expander->i]) || word[expander->i] == '_'))
	{
		if (var_len < sizeof(var_name) - 1)
			var_name[var_len++] = word[expander->i];
		(expander->i)++;
	}
	var_name[var_len] = '\0';
	var_value = get_env_value(data, var_name);
	if (!var_value)
		var_value = "";
	len = ft_strlen(var_value);
	if (resize_result(expander, expander->j + len) == -1)
		return (-1);
	ft_memcpy(&(expander->result[expander->j]), var_value, len);
	expander->j += len;
	return (0);
}

int	handle_regular_char(char c, t_expander *expander)
{
	if (resize_result(expander, expander->j + 1) == -1)
		return (-1);
	expander->result[expander->j++] = c;
	return (0);
}

int	handle_special_dollar(t_data *data, char *word, t_expander *expander)
{
	if (word[expander->i] == '\0')
	{
		if (handle_regular_char('$', expander) == -1)
			return (-1);
	}
	else if (word[expander->i] == '?')
	{
		expander->i++;
		if (handle_dollar_exp(data, expander) == -1)
			return (-1);
	}
	else if (ft_isalpha(word[expander->i]) || word[expander->i] == '_')
	{
		if (handle_variable_exp(data, word, expander) == -1)
			return (-1);
	}
	else
	{
		if (handle_regular_char('$', expander) == -1)
			return (-1);
		if (handle_regular_char(word[expander->i++], expander) == -1)
			return (-1);
	}
	return (0);
}
