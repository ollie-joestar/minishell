/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:22:03 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 10:56:34 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Adds the element new_node at the end of the list lst.
// If the list is NULL, the new_node becomes the first element of the list.
void	ft_lstadd_back(t_list **lst, t_list *new_node)
{
	t_list	*n;

	if (!lst || !new_node)
		return ;
	if (!(*lst))
	{
		*lst = new_node;
		return ;
	}
	n = (*lst);
	while (n->next)
		n = n->next;
	n->next = new_node;
}
