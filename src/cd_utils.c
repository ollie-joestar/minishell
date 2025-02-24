/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:28:43 by oohnivch          #+#    #+#             */
/*   Updated: 2025/02/24 16:30:40 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_error(char *path)
{
	char	*tmp;

	if (!path)
		return ;
	tmp = ft_strjoin("getcwd: ", "cannot access parent directories");
	if (!ft_strncmp(path, "..", 3) || !ft_strncmp(path, ".", 2))
		mspec2(tmp, "No such file or directory\n");
	ft_free(&tmp);
}

char	*get_home(t_data *data)
{
	t_envlist	*env;

	while (data->env && data->env->prev)
		data->env = data->env->prev;
	env = data->env;
	while (env)
	{
		if (!ft_strncmp(env->name, "HOME", 5))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
