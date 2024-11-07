/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:34:53 by hanjkim           #+#    #+#             */
/*   Updated: 2024/04/23 16:31:15 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buffer;
	size_t	amount;

	if (!nmemb || !size)
		return (malloc(0));
	amount = nmemb * size;
	if (nmemb != amount / size)
		return (NULL);
	buffer = (void *)malloc(size * nmemb);
	if (!buffer)
		return (NULL);
	ft_bzero(buffer, size * nmemb);
	return (buffer);
}

/*
#include <stdio.h>

int main()
{
	int size = '\0';

	void * d1 = ft_calloc(size, sizeof(int));
	void * d2 = calloc(size, sizeof(int));
	if (memcmp(d1, d2, size * sizeof(int)))
		return (printf("FAIL"));
	free(d1);
	free(d2);
	return (printf("SUCCESS"));
}*/
