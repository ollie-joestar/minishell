/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:02:16 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 10:59:01 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Iterates the list lst and applies the function f to the content of each element.
// Creates a new list resulting of the successive applications of the function f.
// The function del is the address of the function used to delete the content of an element if needed.
// The original list does not change.
// Returns the new list. NULL if the allocation fails.
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*n_lst;
	t_list	*node;
	void	*cont;

	if (!lst || !f || !del)
		return (NULL);
	n_lst = NULL;
	while (lst)
	{
		cont = f(lst->content);
		node = ft_lstnew(cont);
		if (!node)
		{
			del(cont);
			ft_lstclear(&n_lst, (*del));
			return (n_lst);
		}
		ft_lstadd_back(&n_lst, node);
		lst = lst->next;
	}
	return (n_lst);
}
