/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:01:43 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 10:53:27 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Allocates memory for an array of nmemb elements of size bytes each and sets the memory to zero.
// The allocated memory is large enough to fit nmemb * size bytes.
// The function returns a pointer to the allocated memory.
// If nmemb or size is 0, the function returns NULL.
// If the multiplication of nmemb and size overflows, the function returns NULL.
void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			total_size;
	void			*ptr;

	total_size = size * nmemb;
	if (size && total_size / size != nmemb)
		return (NULL);
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}
