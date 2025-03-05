/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:37:31 by oohnivch          #+#    #+#             */
/*   Updated: 2025/03/05 23:31:21 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	underscore(t_data *data, t_exec *exec)
{
	t_envlist	*list;
	char		*value;
	int			i;

	if (exec_len(data->exec) > 1)
		if (lpid(data))
			return ;
	i = ft_arrlen(exec->av) - 1;
	if (i < 0)
		value = ft_strdup("");
	else
		value = ft_strdup(exec->av[i]);
	if (!value)
		bruh(data, "Malloc fail general_utils.c:30", 69);
	list = find_env(data->env, "_");
	if (list)
		(ft_free(&list->value), list->value = value);
	else
	{
		list = create_env("_", value);
		ft_free(&value);
		if (!list)
			bruh(data, "Malloc fail env.c:125", 69);
		add_env(data->env, list);
	}
}

char	*join2(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	ptr = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		ptr[i] = s1[i];
	while (s2[++j])
		ptr[i + j] = s2[j];
	return (ptr);
}

int	fork1(t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		bruh(data, "spoons!!!!!\n", 69);
	add_pid(data, pid);
	return (pid);
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

void	skip_spaces(char *input, int *i)
{
	while ((input[*i] == ' ' || input[*i] == '\t'))
		(*i)++;
}
