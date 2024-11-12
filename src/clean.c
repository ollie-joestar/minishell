/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:15:50 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/12 16:18:05 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_input(t_exec *exec)
{
	t_input	*tmp;

	while (exec->in)
	{
		tmp = exec->in;
		exec->in = exec->in->next;
		if (tmp->flag == HEREDOC)
			unlink(tmp->file);
		if (tmp->file)
			free(tmp->file);
		free(tmp);
		tmp = NULL;
	}
}

void	clean_output(t_exec *exec)
{
	t_output	*tmp;

	if (exec->out)
	{
		if (exec->out->file)
		{
			free(exec->out->file);
			exec->out->file = NULL;
		}
		free(exec->out);
		exec->out = NULL;
	}
}

void	clean_av(t_exec *exec)
{
	int	i;

	i = 0;
	while (exec->av && *exec->av && exec->av[i])
	{
		free(exec->av[i]);
		exec->av[i] = NULL;
		i++;
	}
	free(exec->av);
	exec->av = NULL;
}

void	clean_exec(t_data *data)
{
	t_exec	*tmp;

	if (data->exec->prev)
		data->exec = data->exec->prev;
	while (data->exec)
	{
		tmp = data->exec;
		data->exec = data->exec->next;
		ft_free(&tmp->cmd);
		clean_av(tmp);
		clean_input(tmp);
		clean_output(tmp);
		free(tmp);
		tmp = NULL;
	}
}
