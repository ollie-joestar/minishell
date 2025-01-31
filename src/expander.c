/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:41:38 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/31 18:27:09 by oohnivch         ###   ########.fr       */
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
	/*while (data->env->prev)*/
	/*	data->env = data->env->prev;*/
	/*env = data->env;*/
	/*while (env)*/
	/*{*/
	/*	if (ft_strncmp(env->name, name, ft_strlen(env->name) + 1) == 0)*/
	/*		return (ft_strdup(env->value));*/
	/*	env = env->next;*/
	/*}*/
	env = find_env(data->env, name);
	if (env)
		return (ft_strdup(env->value));
	else
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
	if (!str[end])
		return (NULL);
	while (str[end] && (ft_isalnum(str[end]) || str[end] == '_'))
	{	
		if (str[end + 1])
			end++;
		else
			break ;
	}
	name = ft_substr(str, start + 1, end - start);
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
	old_i = 0;
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
	ft_free(str);
	*str = new_str;
}

/*
*str>ft_split($<->!alnum) strbefore$<+>!alnum from $till !alnum strafter$<+>!alnum
list while !$  <+list type= word
$<->!alnum <+list type = var
while !$ <+list type = word
$<->!alnum <+list type = var
while !$ <+list


t_token var >>> value 
value ft_splt > tokeb_list >>insert statt var token
*/

void	expand_var_in_str(t_data *data, char **str, int	qf)
{
	char	*name;
	char	*value;
	char	*check;

	name = find_var_name(*str);
	if (!name)
		return ;
	value = expand_ollie(data, name);
	check = ft_strjoin("$", name);
	if ((ft_strlen(*str) == ft_strlen(check)) && !qf && !*value)
	{
		(ft_free(&name), ft_free(&value), ft_free(&check), ft_free(str));
		return ;
	}
	if (!value || !name)
		bruh(data, "Error: malloc failed in expander:122\n" , 1);
	replace_str(str, name, value);
	ft_free(&name);
	ft_free(&value);
}
