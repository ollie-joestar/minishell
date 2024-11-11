/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:03:30 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 10:56:53 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Adds the element new_node at the beginning of the list lst.
// If the list is NULL, the new_node becomes the first element of the list.
// The pointer to the first element of the list is updated.
void	ft_lstadd_front(t_list **lst, t_list *new_node)
{
	if (!lst || !new_node)
		return ;
	new_node->next = *lst;
	*lst = new_node;
}
