/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:59:00 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/31 17:13:19 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// joins "minishell: " and str and prints the error message
void	mspe(char *str)
{
	char	*error;

	error = join2("minishell: ", str);
	perror(error);
	ft_free(&error);
}

// joins "minishell: ", str1 & str2 and prints the error message
void	mspe2(char *str1, char *str2)
{
	char	*error;
	char	*tmp;

	tmp = join2("minishell: ", str1);
	error = join2(tmp, ": ");
	ft_free(&tmp);
	tmp = error;
	error = join2(tmp, str2);
	ft_free(&tmp);
	perror(error);
	ft_free(&error);
}

// joins "minishell: " and str and prints the CUSTOM MESSAGE!
void	mspec(char *str)
{
	char	*error;

	error = join2("minishell: ", str);
	ft_putstr_fd(error, 2);
	ft_free(&error);
}

// joins "minishell: ", str1 & str2 and prints the CUSTOM MESSAGE!
void	mspec2(char *str1, char *str2)
{
	char	*error;
	char	*tmp;

	tmp = join2("minishell: ", str1);
	error = join2(tmp, ": ");
	ft_free(&tmp);
	tmp = error;
	error = join2(tmp, str2);
	ft_free(&tmp);
	ft_putstr_fd(error, 2);
	ft_free(&error);
}

void	mspec3(char *str1, char *str2, char *str3)
{
	char	*error;
	char	*tmp;

	tmp = join2("minishell: ", str1);
	error = join2(tmp, ": ");
	ft_free(&tmp);
	tmp = error;
	error = join2(tmp, str2);
	ft_free(&tmp);
	tmp = error;
	error = join2(tmp, str3);
	ft_free(&tmp);
	ft_putstr_fd(error, 2);
	ft_free(&error);
}
/*static int	golden(va_list args, char **result)*/
/*{*/
/*	char	*string;*/
/*	char	*tmp;*/
/**/
/*	string = va_arg(args, char *);*/
	/*ft_printerr("Combining: %s\n", string);*/
/*	if (!string)*/
/*	{*/
		/*ft_printerr("the string in requiem is NULL\n");*/
/*		return (-1);*/
/*	}*/
/*	tmp = *result;*/
	/*ft_printerr("\t\ttmp: %s\n", tmp);*/
/*	*result = experience(*result, string);*/
	/*ft_printerr("\t\tresult: %s\n", *result);*/
/*	if (!*result)*/
/*	{*/
		/*ft_printerr("the result in requiem is NULL\n");*/
/*		return (ft_free(&tmp), -1);*/
/*	}*/
/*	ft_free(&tmp);*/
/*	return (0);*/
/*}*/
/**/
/*int	requiem(int	n, ...)*/
/*{*/
/*	va_list	args;*/
/*	char	*result;*/
/*	int		return_value;*/
/*	int		check;*/
/**/
	/*ft_printerr("Golden experience requiem!\n");*/
/*	if (n < 1)*/
/*		return (-1);*/
/*	result = NULL;*/
/*	va_start(args, n);*/
/*	while (n--)*/
/*	{*/
/*		check = golden(args, &result);*/
/*		if (check == -1)*/
/*		{*/
			/*ft_printerr("the check in requiem is -1 when combining string number %d\n", debug - n);*/
/*			break ;*/
/*		}*/
/*	}*/
/*	va_end(args);*/
/*	return_value = ft_putstr_fd(result, 2);*/
/*	ft_free(&result);*/
/*	return (return_value);*/
/*}*/
