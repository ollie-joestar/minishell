/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:15:50 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/21 16:35:34 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_input(t_exec *exec)
{
	t_input	*tmp;

	while (exec->in && exec->in->prev)
		exec->in = exec->in->prev;
	while (exec->in)
	{
		tmp = exec->in;
		exec->in = exec->in->next;
		if (tmp->file)
			ft_free(&tmp->file);
		free(tmp);
		tmp = NULL;
	}
}

void	clean_output(t_exec *exec)
{
	t_output	*tmp;

	while (exec->out && exec->out->prev)
		exec->out = exec->out->prev;
	while (exec->out)
	{
		tmp = exec->out;
		exec->out = exec->out->next;
		if (tmp->file)
			ft_free(&tmp->file);
		free(tmp);
		tmp = NULL;
	}
}

void	clean_exec(t_data *data)
{
	t_exec	*tmp;

	if (data->exec && data->exec->prev)
		data->exec = data->exec->prev;
	while (data->exec)
	{
		tmp = data->exec;
		data->exec = data->exec->next;
		/*ft_printf("Cleaning exec\n");*/
		ft_free(&tmp->cmd);
		free_arr(&tmp->av);
		clean_input(tmp);
		clean_output(tmp);
		free(tmp);
		tmp = NULL;
	}
}
