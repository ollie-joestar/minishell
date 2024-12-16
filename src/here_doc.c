/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:39:47 by oohnivch          #+#    #+#             */
/*   Updated: 2024/12/16 15:08:03 by hanjkim          ###   ########.fr       */
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
	name = ft_calloc(37, sizeof(char));
	if (!name)
		return (close(fd), NULL);
	if (read(fd, name, 31) != 31)
		return (close(fd), ft_free(&name), NULL);
	close(fd);
	i = 31;
	while (--i >= 0)
		name[i + 5] = base[(unsigned char)name[i] % 16];
	name[0] = '/';
	name[1] = 't';
	name[2] = 'm';
	name[3] = 'p';
	name[4] = '/';
	return (name);
}

char	*here_doc(t_data *data, char *l, int to_expand)
{
	int		fd;
	char	*line;
	char	*file;
	char	*lim;

	file = random_name();
	lim = ft_strjoin(l, "\n");
	fd = open(file, O_CREAT | O_RDWR, 0664);
	if (fd < 0)
		bruh(data, "minishell: failed here_doc creation", 2);
	while (1)
	{
		ft_free(&line);
		line = readline("> ");
		if (to_expand)
			expand_var_in_str(data, &line);
		if (!ft_strncmp(line, lim, ft_strlen(lim) + 1))
			break ;
		if (line)
			write(fd, line, ft_strlen(line));
	}
	(ft_free(&line), ft_free(&lim));
	close(fd);
	return (file);
}
