/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:39:47 by oohnivch          #+#    #+#             */
/*   Updated: 2024/12/02 15:55:08 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*random_name(void)
{
	int		i;
	int		fd;
	char	*name;
	char	*base;

	base = "0123456789abcdef";
	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
		return (NULL);
	name = ft_calloc(32, sizeof(char));
	if (!name)
		return (close(fd), NULL);
	if (read(fd, name, 31) != 31)
		return (close(fd), ft_free(&name), NULL);
	close(fd);
	i = -1;
	while (++i < 31)
		name[i] = base[(unsigned char)name[i] % 16];
	return (name);
}

char	*here_doc(t_data *data, char *l)
{
	int		fd;
	char	*line;
	char	*file;
	char	*buffer;
	char	*lim;

	line = random_name();
	file = ft_strjoin("/tmp/", line);
	ft_free(&line);
	lim = ft_strjoin(l, "\n");
	fd = open(file, O_CREAT | O_RDWR, 0664);
	if (fd < 0)
		bruh(data, "minishell: failed here_doc creation", 2);
	buffer = NULL;
	while (1)
	{
		write(1, "> ", 2);
		ft_free(&line);
		line = get_next_line_2(0, &buffer, &data->status);
		/*expand(&line, data);*/
		if (!ft_strncmp(line, lim, ft_strlen(lim) + 1))
			break ;
		expand_var_in_str(data, &line);
		if (line)
			write(fd, line, ft_strlen(line));
	}
	ft_free(&line);
	ft_free(&lim);
	ft_free(&buffer);
	close(fd);
	return (file);
}
