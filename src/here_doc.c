/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:37:46 by oohnivch          #+#    #+#             */
/*   Updated: 2025/03/05 23:50:45 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_heredoc_signal(t_data *data, char **ln, char **f, int fd)
{
	if (g_signal == SIGINT)
	{
		ft_free(ln);
		close(fd);
		unlink(*f);
		fd = open(*f, O_CREAT | O_RDWR, 0664);
		if (fd < 0)
			bruh(data, "minishell: failed here_doc.c:24", 2);
		close(fd);
		data->status = 130;
		return (1);
	}
	return (0);
}

static char	*random_name(void)
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

int	warning_heredoc(char *line, char *lim)
{
	char	*warning;

	warning = "warning: here-document delimited by end-of-file (wanted `";
	if (!line)
	{
		if (g_signal == SIGINT)
			return (1);
		return (mspec3(warning, lim, "')\n"), 1);
	}
	if (!ft_strncmp(line, lim, ft_strlen(lim) + 1))
		return (1);
	return (0);
}

void	free_and_expand(t_data *data, char **line)
{
	char	*tmp;

	tmp = expand(data, *line);
	ft_free(line);
	if (!tmp)
		bruh(data, "minishell: failed here_doc.c:79", 2);
	*line = tmp;
}

char	*here_doc(t_data *data, char *l, int dont_expand)
{
	int		fd;
	char	*line;
	char	*file;

	line = NULL;
	file = random_name();
	if (!file)
		bruh(data, "minishell: failed here_doc name generation", 2);
	fd = open(file, O_CREAT | O_RDWR, 0664);
	if (fd < 0)
		(ft_free(&file), bruh(data, "minishell: failed here_doc creation", 2));
	while (1)
	{
		if (handle_heredoc_signal(data, &line, &file, fd))
			return (ft_free(&line), ft_free(&file), NULL);
		line = readline("> ");
		hd_sigint_check(data, &line, &file, fd);
		if (warning_heredoc(line, l))
			break ;
		if (!dont_expand)
			free_and_expand(data, &line);
		if (check_and_write_line(fd, &line))
			break ;
	}
	return (close(fd), ft_free(&line), file);
}
