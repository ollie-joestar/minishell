/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:39:47 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/31 15:32:48 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*handle_heredoc(t_data *data, t_token *redirection_token,
						t_token *filename_token)
{
	int		dont_expand;
	char	*temp_word;
	char	*here_result;

	dont_expand = (filename_token->segments->double_quoted
			|| filename_token->segments->single_quoted);
	temp_word = join_segments(filename_token);
	if (!temp_word)
		bruh(data, "Failed to join filename segments for HEREDOC", 2);
	here_result = here_doc(data, temp_word, dont_expand);
	ft_free(&temp_word);
	free_token_node(&filename_token);
	filename_token = create_token_from_string(here_result);
	ft_free(&here_result);
	if (!filename_token)
		return (NULL);
	filename_token->type = HEREDOC;
	filename_token->next = redirection_token->next;
	return (filename_token);
}

static int	handle_heredoc_signal(t_data *data, char **line, char **file, int fd)
{
	if (g_signal == SIGINT)
	{
		ft_free(line);
		safe_close(fd);
		unlink(*file);
		fd = open(*file, O_CREAT | O_RDWR, 0664);
		if (fd < 0)
			bruh(data, "minishell: failed here_doc.c:49", 2);
		safe_close(fd);
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
		return (safe_close(fd), NULL);
	if (read(fd, name, 31) != 31)
		return (safe_close(fd), ft_free(&name), NULL);
	safe_close(fd);
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

static int	warning_heredoc(char *line, char *lim)
{
	char	*tmp;
	char	*warning;

	warning = "warning: here-document delimited by end-of-file (wanted `";
	if (!line)
	{
		tmp = ft_strjoin(warning, lim);
		line = ft_strjoin(tmp, "')\n");
		ft_free(&tmp);
		mspec(line);
		ft_free(&line);
		return (1);
	}
	if (!ft_strncmp(line, lim, ft_strlen(lim) + 1))
		return (1);
	return (0);
}

char	*here_doc(t_data *data, char *l, int dont_expand)
{
	int		fd;
	char	*line;
	char	*file;

	g_signal = 0;
	file = random_name();
	fd = open(file, O_CREAT | O_RDWR, 0664);
	if (fd < 0)
		bruh(data, "minishell: failed here_doc creation", 2);
	while (1)
	{
		line = readline("> ");
		if (handle_heredoc_signal(data, &line, &file, fd))
			return (file);
		if (warning_heredoc(line, l))
			break ;
		if (!dont_expand)
			line = expand(data, line);
		if (line)
			write(fd, line, ft_strlen(line));
		(write(fd, "\n", 1), ft_free(&line));
	}
	return (safe_close(fd), ft_free(&line), file);
}
