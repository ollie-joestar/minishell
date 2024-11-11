/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:15:50 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 16:45:49 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_input(t_redir *redir)
{
	t_input	*tmp;

	while (redir->in)
	{
		tmp = redir->in;
		redir->in = redir->in->next;
		if (tmp->flag == HEREDOC)
			unlink(tmp->file);
		if (tmp->file)
			free(tmp->file);
		free(tmp);
		tmp = NULL;
	}
}

void	clean_output(t_redir *redir)
{
	t_output	*tmp;

	if (redir->out)
	{
		if (redir->out->file)
		{
			free(redir->out->file);
			redir->out->file = NULL;
		}
		free(redir->out);
		redir->out = NULL;
	}
}

void	clean_redir(t_exec *exec)
{
	clean_input(exec->redir);
	clean_output(exec->redir);
	free(exec->redir);
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
