/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:44:29 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 10:59:23 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Allocates and returns a new element.
// The variable content is initialized with the value of the parameter content.
// The variable next is initialized to NULL.
// Returns the new element.
t_list	*ft_lstnew(void *content)
{
	t_list		*node;

	node = (t_list *) malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
