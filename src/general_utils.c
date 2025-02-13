/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:36:14 by oohnivch          #+#    #+#             */
/*   Updated: 2025/02/13 15:44:05 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// safe fork function
// if fork fails, it prints the error message and exits the program
// if fork succeeds, it adds the pid to the pid list
// returns the pid of the forked process

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
		bruh(data, "spoons!!!!!\n", 1);
	add_pid(data, pid);
	return (pid);
}

int	checkfile(char *file)
{
	char *path_to_file;
	int	i;
	int	name_len;

	i = 1;
	name_len = ft_strlen(file) - 1;
	if (name_len <= 0)
		return (-1);
	while (file[name_len - i] != '/' && i <= name_len)
		i++;
	if (i == name_len)
		return (0);
	path_to_file = ft_substr(file, 0, name_len - i);
	if (access(path_to_file, F_OK) == 0)
	{
		if (access(path_to_file, W_OK) == -1)
		{
			ft_free(&path_to_file);
			return (-1);
		}
		ft_free(&path_to_file);
	}
	else
		return (-1);
	return (0);
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

int	safe_close(int fd)
{
	int	ret;

	ret = 0;
	/*ft_printerr("Closing fd: %d\n", fd);*/
	ret = close(fd);
	if (ret == -1)
		mspe2("failed to close fd", ft_strjoin(ft_itoa(fd), "\n"));
	return (ret);
	/*if (fd == -1)*/
	/*	mspe("Tried to close invalid fd\n");*/
	/*if (fd == 0)*/
	/*	mspe("Tried to close stdin fd\n");*/
	/*if (fd == 1)*/
	/*	mspe("Tried to close stdout fd\n");*/
	/*if (fd == 2)*/
	/*	mspe("Tried to close errno fd\n");*/
	/*if (fd > 2)*/
	/*{*/
	/*mspec("closing fd\n");*/
	/*ft_printerr("Closing fd: %d\n", fd);*/
		/*if (-1 == close(fd))*/
		/*	mspe("failed to close fd\n");*/
	/*}*/
}

void	skip_spaces(char *input, int *i)
{
	while ((input[*i] == ' ' || input[*i] == '\t'))
		(*i)++;
}
