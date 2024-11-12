/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:15:50 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/12 16:01:29 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_input(t_data *data)
{
	t_input	*tmp;

	while (data->in)
	{
		tmp = data->in;
		data->in = data->in->next;
		if (tmp->flag == HEREDOC)
			unlink(tmp->file);
		if (tmp->file)
			free(tmp->file);
		free(tmp);
		tmp = NULL;
	}
}

void	clean_output(t_data *data)
{
	t_output	*tmp;

	if (data->out)
	{
		if (data->out->file)
		{
			free(data->out->file);
			data->out->file = NULL;
		}
		free(data->out);
		data->out = NULL;
	}
}

void	clean_redir(t_exec *exec)
{
	clean_input(exec->data);
	clean_output(exec->data);
	free(exec->data);
	exec->redir = NULL;
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
		if (tmp->redir)
			clean_redir(tmp);
		free(tmp);
		tmp = NULL;
	}
}
