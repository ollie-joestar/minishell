/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:30:00 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 10:58:17 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Iterates the list lst and applies the function f to the content of each element.
// The function f is the address of the function used to iterate the list.
// The function does not return anything.
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*n;

	if (!lst || !f)
		return ;
	n = lst->next;
	if (n != NULL)
		ft_lstiter(n, f);
	(f)(lst->content);
}
