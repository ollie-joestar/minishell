/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:51:50 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/21 12:42:12 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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
