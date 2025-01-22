/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:36:14 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/22 14:02:09 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	bruh(t_data *data, char *s, int status)
{
	if (s)
		(ft_putstr_fd(s, 2), ft_putstr_fd("\n", 2));
	clean_exec(data);
	free_env_list(data->env);
	free_arr(&data->ev);
	free_arr(&data->path);
	ft_free(&data->line);
	free_tokens(data);
	/*clear_history();*/
	rl_clear_history();
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

void	skip_spaces(char *input, int *i)
{
	while ((input[*i] == ' ' || input[*i] == '\t'))
		(*i)++;
}

static char	*experience(char const *s1, char const *s2)
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

static int	golden(va_list args, char **result)
{
	char	*string;
	char	*tmp;

	string = va_arg(args, char *);
	/*ft_printerr("Combining: %s\n", string);*/
	if (!string)
	{
		/*ft_printerr("the string in requiem is NULL\n");*/
		return (-1);
	}
	tmp = *result;
	/*ft_printerr("\t\ttmp: %s\n", tmp);*/
	*result = experience(*result, string);
	/*ft_printerr("\t\tresult: %s\n", *result);*/
	if (!*result)
	{
		/*ft_printerr("the result in requiem is NULL\n");*/
		return (ft_free(&tmp), -1);
	}
	ft_free(&tmp);
	return (0);
}

int	requiem(int	n, ...)
{
	va_list	args;
	char	*result;
	int		return_value;
	int		check;

	/*ft_printerr("Golden experience requiem!\n");*/
	if (n < 1)
		return (-1);
	result = NULL;
	va_start(args, n);
	while (n--)
	{
		check = golden(args, &result);
		if (check == -1)
		{
			/*ft_printerr("the check in requiem is -1 when combining string number %d\n", debug - n);*/
			break ;
		}
	}
	va_end(args);
	return_value = ft_putstr_fd(result, 2);
	ft_free(&result);
	return (return_value);
}
