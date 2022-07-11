/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hdoc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 22:50:53 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/11 10:24:50 by gtoubol          ###   ########.fr       */
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
#include "g_minishell.h"

static int	create_hdoc_loop(char *eof, int fd)
{
	char	*line;
	int		len_line;
	long	i;

	line = NULL;
	i = -1;
	while (1 && is_interupted() == 0 && (++i >= 0))
	{
		free(line);
		line = readline("> ");
		if (line == NULL)
		{
			ft_fprintf(2, "minishell: warning: here-document at line %i \
delimited by end-of-file (wanted `%s')\n", i, eof);
			return (0);
		}
		len_line = ft_strlen(line);
		if (eof && ft_strcmp(eof, line) == 0)
			break ;
		write(fd, line, len_line);
		write(fd, "\n", 1);
	}
	if (is_interupted())
		write(2, "\n", 1);
	return (free(line), 0);
}

// static int	create_hdoc_loop(char *eof, int fd)
// {
// 	char	*line;
// 	int		len_line;

// 	line = NULL;
// 	while (1)
// 	{
// 		free(line);
// 		line = readline("> ");
// 		if (!line)
// 			return (0);
// 		len_line = ft_strlen(line);
// 		if (eof && !ft_strcmp(eof, line))
// 			break ;
// 		else if (!eof && !line[0])
// 			break ;
// 		write (fd, line, len_line);
// 		write (fd, "\n", 1);
// 	}
// 	free(line);
// 	return (0);
// }

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
	}
	return (out);
}

static int	create_hdoc(char **hdoc)
{
	char	*hdoc_name;
	char	*eof;
	int		hdoc_fd;

	hdoc_name = tmp_filename();
	if (!hdoc_name)
		return (1);
	hdoc_fd = open(hdoc_name, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (hdoc_fd == -1)
		return (free(hdoc_name), -1);
	eof = ft_strdup(*hdoc);
	if (!eof)
		return (error_alloc(), 1);
	free(*hdoc);
	*hdoc = hdoc_name;
	if (create_hdoc_loop(eof, hdoc_fd))
		return (clean_hdoc(hdoc_name, eof, hdoc_fd, 1));
	free(eof);
	close(hdoc_fd);
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
	free(*hdoc);
	*hdoc = hdoc_name;
	if (create_hdoc_loop(eof, hdoc_fd))
		return (clean_hdoc(hdoc_name, eof, hdoc_fd, 1));
	free(eof);
	close(hdoc_fd);
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
