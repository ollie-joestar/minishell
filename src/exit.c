/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:19:32 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/21 11:51:44 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_data *data, t_exec *exec)
{
	if (exec->av && exec->av[1])
		data->status = ft_atoi(exec->av[1]);
	bruh(data, "exit", data->status);
}
