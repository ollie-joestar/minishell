/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:59:00 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/23 13:59:33 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*experience(char const *s1, char const *s2)
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
