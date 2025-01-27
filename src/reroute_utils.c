/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reroute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:03:32 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/27 12:47:27 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**/
/*t_input	*get_first_input(t_input *input)*/
/*{*/
/*	if (!input)*/
/*		return (NULL);*/
/*	while (input->prev)*/
/*		input = input->prev;*/
/*	return (input);*/
/*}*/
/**/
/*t_output	*get_first_output(t_output *output)*/
/*{*/
/*	if (!output)*/
/*		return (NULL);*/
/*	while (output->prev)*/
/*		output = output->prev;*/
/*	return (output);*/
/*}*/

t_redir	*get_first_redir(t_redir *redir)
{
	if (!redir)
		return (NULL);
	while (redir->prev)
		redir = redir->prev;
	return (redir);
}

int	has_input(t_exec *exec)
{
	t_redir	*redir;

	if (!exec || !exec->redir)
		return (0);
	redir = exec->redir;
	while (redir->prev)
		redir = redir->prev;
	while (redir)
	{
		if (redir->type == INPUT || redir->type == HEREDOC)
			return (1);
		redir = redir->next;
	}
	return (0);
}

int	has_output(t_exec *exec)
{
	t_redir	*redir;

	if (!exec || !exec->redir)
		return (0);
	redir = exec->redir;
	while (redir->prev)
		redir = redir->prev;
	while (redir)
	{
		if (redir->type == REPLACE || redir->type == APPEND)
			return (1);
		redir = redir->next;
	}
	return (0);
}
