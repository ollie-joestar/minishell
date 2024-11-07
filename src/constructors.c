/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:38:56 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/07 16:51:46 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec	*create_exec(char **av, t_redir *redir)
{
	t_exec	*new_node;

	new_node = ft_calloc(1, sizeof(t_exec));
	if (!new_node)
		return (NULL);
	new_node->type = check_builtin(av[0]);
	if (new_node->type == 0)
		return (NULL);
	new_node->av = av;
	new_node->redir = redir;
	return (new_node);
}

t_exec *add_node(t_data *data, t_exec *head)
{
	t_exec		*tmp;
	t_exec		*new_node;

	new_node = create_e_data(av, redir);
	if (!new_node)
		bruh(data, "malloc failed\n", 1);
	if (!head)
		return (new_node);
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	new_node->prev = tmp;
	return (head);
}

