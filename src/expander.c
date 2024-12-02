/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:41:38 by oohnivch          #+#    #+#             */
/*   Updated: 2024/12/02 16:08:36 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_ollie(t_data *data, char *name)
{
	t_envlist	*env;

	if (!name)
		return (NULL);
	if (ft_strncmp(name, "?", 2) == 0)
		return (ft_strdup(ft_itoa(data->status)));
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

char	*find_var_name(char *str)
{
	char	*name;
	int		start;
	int		end;

	start = 0;
	end = 0;
	name = NULL;
	while (str[start] && str[start] != '$')
		start++;
	end = start + 1;
	while (str[end] && (ft_isalnum(str[end]) || str[end] == '_'))
		end++;
	if (end - start == 1)
		return (NULL);
	name = ft_substr(str, start + 1, end - start - 1);
	if (!name)
		bruh(NULL, "Error: malloc failed in expander:53\n", 1);
	return (name);
}

static void	replace_str(char **str, char *name, char *value)
{
	char	*new_str;
	char	*tmp;
	int		old_i;
	int		new_i;

	new_i = 0;
	old_i = ft_strlen(*str) - ft_strlen(name) + ft_strlen(value) + 1;
	new_str = ft_calloc(sizeof(char), old_i);
	if (!new_str)
		bruh(NULL, "Error: malloc failed in expander:68\n", 1);
	while ((*str)[old_i] && (*str)[old_i] != '$')
		new_str[new_i++] = (*str)[old_i++];
	tmp = value;
	while (*tmp)
		new_str[new_i++] = *tmp++;
	old_i += ft_strlen(name) + 1;
	while ((*str)[old_i])
		new_str[new_i++] = (*str)[old_i++];
	new_str[new_i] = '\n';
	free(*str);
	*str = NULL;
	*str = new_str;
}

void	expand_var_in_str(t_data *data, char **str)
{
	char	*name;
	char	*value;

	name = find_var_name(*str);
	if (!name)
		return ;
	value = expand_ollie(data, name);
	if (!value || !name)
		bruh(data, "Error: malloc failed in expander:91\n" , 1);
	replace_str(str, name, value);
	ft_free(&name);
	ft_free(&value);
}
