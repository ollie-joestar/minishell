/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:51:50 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 10:57:28 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Deletes and frees the memory of the element and all its successors.
// The function del is the address of the function used to delete the content of the element.
// The function does not free the memory of the content of the elements.
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*n;

	if (!lst || !del || !(*lst))
		return ;
	n = (*lst)->next;
	if (n != NULL)
		ft_lstclear(&n, del);
	(del)((*lst)->content);
	free(*lst);
	*lst = NULL;
}
