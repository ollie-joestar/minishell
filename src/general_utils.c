/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:18:21 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/24 19:03:05 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_not_meta(char c)
{
	return (c != '>' && c != '<' && c != '|' &&  c != ' ' && c != '$' && c != '\'' && c != '\"');
}

void	bruh(t_data *data, char *s, int status)
{
	if (s)
		(ft_putstr_fd(s, 2), ft_putstr_fd("\n", 2));
	clean_exec(data);
	free_env_list(data);
	free_arr(&data->ev);
	free_arr(&data->path);
	ft_free(&data->line);
	free_tokens(data);
	clear_history();
	/*free_history();*/
	if (data)
		free(data);
	exit(status);
}

size_t	ft_arrlen(char **arr)
{
	size_t	i;

	if (!arr || !*arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char *ft_strjoin_and_free(char *s1, char *s2)
{
	char *new_str;
	size_t len1;
	size_t len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_str = ft_calloc(len1 + len2 + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, s1, len1);
	ft_memcpy(new_str + len1, s2, len2);
	ft_free(&s1);
	ft_free(&s2);
	return (new_str);
}
