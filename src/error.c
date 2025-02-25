/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:59:00 by oohnivch          #+#    #+#             */
/*   Updated: 2025/02/25 10:44:35 by oohnivch         ###   ########.fr       */
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
	tmp = join2(error, ": ");
	ft_free(&error);
	error = join2(tmp, str3);
	ft_free(&tmp);
	ft_putstr_fd(error, 2);
	ft_free(&error);
}
