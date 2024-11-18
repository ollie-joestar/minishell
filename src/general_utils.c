/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:18:21 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/18 15:38:34 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_not_meta(char c)
{
	return (c != '>' && c != '<' && c != '|' &&  c != ' ' && c != '$' && c != '\'' && c != '\"');
}

void	bruh(t_data *data, char *s, int status)
{
	if (s)
		ft_putstr_fd(s, 2);
	clean_exec(data);
	free_env_list(data);
	free_arr(data->ev);
	free_arr(data->path);
	ft_free(&data->line);
	free_tokens(data);
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
