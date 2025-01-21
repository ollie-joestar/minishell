/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:59:31 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/21 12:38:36 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_buffjoin(char **buffer, char **content)
{
	size_t	size;
	char	*ptr;
	char	*c_ptr;
	size_t	i;

	if (!*buffer && !*content)
		return (NULL);
	size = ft_strlen(*buffer) + ft_strlen(*content);
	ptr = ft_calloc((size + 1), sizeof(char));
	if (ptr == NULL)
		return (ft_free(buffer), ft_free(content), NULL);
	c_ptr = ptr;
	i = 0;
	while (*buffer && (*buffer)[i])
		*c_ptr++ = (*buffer)[i++];
	i = 0;
	while (*content && (*content)[i])
		*c_ptr++ = (*content)[i++];
	ft_free(buffer);
	return (ptr);
}

char	*ft_move_buffer(char **old, size_t start, size_t len)
{
	size_t	i;
	char	*new;

	if (!old || !*old)
		return (NULL);
	if (start > ft_strlen(*old))
		len = 0;
	else if (start + len > ft_strlen(*old))
		len = ft_strlen(*old) - start;
	new = ft_calloc((len + 1), sizeof(char));
	if (new == NULL)
		return (ft_free(old), NULL);
	if (!len)
	{
		ft_free(old);
		return (new);
	}
	i = 0;
	while (i < len && (*old)[i + start])
	{
		new[i] = (unsigned char)(*old)[i + start];
		i++;
	}
	ft_free(old);
	return (new);
}

char	*ft_parseline(char **buffer, int *exit_code)
{
	size_t			i;
	size_t			len;
	unsigned char	*cont;

	if (!(*buffer) || !(*buffer[0]))
		return (*exit_code = -1, NULL);
	len = ft_linelen(*buffer);
	cont = ft_calloc(len + 1, sizeof(char));
	if (!cont)
		return (*exit_code = -1, ft_free(buffer), NULL);
	i = 0;
	while (i < len)
	{
		cont[i] = (unsigned char)(*buffer)[i];
		i++;
	}
	*buffer = ft_move_buffer(buffer, len, BUFFER_SIZE);
	if (!(*buffer))
		return (ft_free((char **)&cont), ft_free(buffer), NULL);
	return ((char *)cont);
}

char	*end_check(char **buffer, char *content, ssize_t bytes, int *e)
{
	if (bytes == 0)
		ft_free(buffer);
	*e = 0;
	return (content);
}

char	*get_next_line(int fd, int *exit_code)
{
	char		*content;
	ssize_t		bytes;
	static char	*buffer;

	bytes = 1;
	if (fd < 0)
		return (*exit_code = -1, NULL);
	content = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!content)
		return (*exit_code = -1, ft_free(&buffer), NULL);
	while (!ft_nlcheck(buffer) && bytes != 0)
	{
		bytes = read(fd, content, BUFFER_SIZE);
		if (bytes == -1)
			return (*exit_code = -1, ft_free(&buffer), ft_free(&content), NULL);
		content[bytes] = 0;
		if (bytes != 0)
			buffer = ft_buffjoin(&buffer, &content);
		if (!buffer)
			return (*exit_code = 0, ft_free(&content), NULL);
	}
	ft_free(&content);
	content = ft_parseline(&buffer, exit_code);
	return (end_check(&buffer, content, bytes, exit_code));
}
