/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hdoc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 22:50:53 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/30 11:07:03 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "lexer.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

static int	create_hdoc_loop(char *eof, int fd)
{
	char	*line;
	int		len_line;

	line = NULL;
	while (1)
	{
		free(line);
		line = get_next_line(0);
		if (!line)
			return (0);
		len_line = ft_strlen(line);
		if (eof && !ft_strncmp(eof, line, len_line - 1)
			&& !eof[len_line - 1])
			break ;
		else if (!eof && !line[0])
			break ;
		write (fd, line, len_line);
	}
	free(line);
	return (0);
}

static int	clean_hdoc(char *name, void *ptr, int fd, int out)
{
	if (ptr)
		free(ptr);
	if (fd > 0)
		close(fd);
	if (name)
	{
		if (unlink(name) == -1)
			return (-1);
		free(name);
	}
	return (out);
}

static int	create_hdoc(char **hdoc)
{
	char	*hdoc_name;
	int		hdoc_fd;

	hdoc_name = tmp_filename();
	if (!hdoc_name)
		return (1);
	hdoc_fd = open(hdoc_name, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (hdoc_fd == -1)
		return (free(hdoc_name), -1);
	if (create_hdoc_loop(*hdoc, hdoc_fd))
		return (clean_hdoc(hdoc_name, NULL, hdoc_fd, 1));
	close(hdoc_fd);
	free(*hdoc);
	*hdoc = hdoc_name;
	return (0);
}

static int	create_hdoc_q(char **hdoc)
{
	char	*eof;
	char	*hdoc_name;
	int		hdoc_fd;

	hdoc_name = tmp_filename_q();
	if (!hdoc_name)
		return (1);
	hdoc_fd = open(hdoc_name, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (hdoc_fd == -1)
		return (free(hdoc_name), -1);
	eof = quotes_hdoc(*hdoc);
	if (create_hdoc_loop(eof, hdoc_fd))
		return (clean_hdoc(hdoc_name, eof, hdoc_fd, 1));
	free(eof);
	close(hdoc_fd);
	free(*hdoc);
	*hdoc = hdoc_name;
	return (0);
}

int	set_hdoc(char **hdoc)
{
	int	err;

	if (ft_strchr(*hdoc, '"') || ft_strchr(*hdoc, '\''))
	{
		err = create_hdoc_q(hdoc);
		if (err)
			return (1);
		if (err == -1)
			return (perror("Error: hdoc "), 1);
	}
	else
	{
		err = create_hdoc(hdoc);
		if (err)
			return (1);
		if (err == -1)
			return (perror("Error: hdoc "), 1);
	}
	return (0);
}
