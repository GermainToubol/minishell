/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hdoc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 22:50:53 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/30 01:47:39 by fmauguin         ###   ########.fr       */
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

static int	create_hdoc_loop(char *eof)
{
	char	*line;

	line = NULL;
	while (1)
	{
		free(line);
		line = readline("> ");
		if (!line)
			return (1);
		if (eof && !ft_strcmp(line, eof))
			break ;
		else if (!eof && !line[0])
			break ;
		write (4, line, ft_strlen(line));
		write (4, "\n", 1);
	}
	free(line);
	return (0);
}

static int	create_hdoc(char **hdoc)
{
	char	*hdoc_name;
	int		hdoc_fd;

	hdoc_name = tmp_filename();
	if (!hdoc)
		return (1);
	hdoc_fd = open(hdoc_name, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (hdoc_fd == -1)
		return (free(hdoc_name), -1);
	if (dup2(hdoc_fd, 4) == -1)
		return (free(hdoc_name), -1);
	if (create_hdoc_loop(*hdoc))
		return (free(hdoc_name), 1);
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
	if (!hdoc)
		return (1);
	hdoc_fd = open(hdoc_name, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (hdoc_fd == -1)
		return (free(hdoc_name), -1);
	if (dup2(hdoc_fd, 4) == -1)
		return (free(hdoc_name), -1);
	eof = quotes_hdoc(*hdoc);
	if (create_hdoc_loop(eof))
	{
		free(hdoc_name);
		return (free(eof), 1);
	}
	free(eof);
	close(hdoc_fd);
	free(*hdoc);
	*hdoc = hdoc_name;
	return (0);
}

int	get_hdoc(char **hdoc)
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
