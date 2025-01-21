/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:47:26 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/21 12:37:29 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*end_check(char **buffer, char *content, ssize_t bytes, int *e)
{
	if (bytes == 0)
		ft_free(buffer);
	*e = 0;
	return (content);
}

char	*get_next_line_2(int fd, char **buffer, int *exit_code)
{
	char		*content;
	ssize_t		bytes;

	bytes = 1;
	if (fd < 0)
		return (*exit_code = -1, NULL);
	content = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!content)
		return (*exit_code = -1, ft_free(buffer), NULL);
	while (!ft_nlcheck(*buffer) && bytes != 0)
	{
		bytes = read(fd, content, BUFFER_SIZE);
		if (bytes == -1)
			return (*exit_code = -1, ft_free(buffer), ft_free(&content), NULL);
		content[bytes] = 0;
		if (bytes != 0)
			*buffer = ft_buffjoin(buffer, &content);
		if (!*buffer)
			return (*exit_code = 0, ft_free(&content), NULL);
	}
	ft_free(&content);
	content = ft_parseline(buffer, exit_code);
	return (end_check(buffer, content, bytes, exit_code));
}
