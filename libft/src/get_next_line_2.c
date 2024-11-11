/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:47:26 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 11:20:03 by oohnivch         ###   ########.fr       */
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

// Reads a line from a file descriptor and returns it without the newline character.
// Returns NULL in case of an error or when the file has ended.
// Changes the value of the exit_code variable to -1 in case of an error.
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
