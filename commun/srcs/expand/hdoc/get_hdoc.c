/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hdoc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 01:53:05 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/30 12:48:19 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "utils.h"
#include "libft.h"
#include "expand.h"
#include <sys/types.h>
#include <sys/wait.h>

int	read_hdoc(int hdoc_fd, int out_fd)
{
	ssize_t	r;
	char	buffer[BUFFER_SIZE + 1];
	char	*line;

	r = 1;
	while (r)
	{
		r = read(hdoc_fd, &buffer, BUFFER_SIZE);
		if (r == -1)
			return (-1);
		if (r == 0)
			break ;
		buffer[r] = '\0';
		if (!ft_strchr(buffer, '$'))
			write (out_fd, buffer, r);
		else
		{
			line = expand_var(buffer);
			if (line)
				write (out_fd, line, ft_strlen(line));
			free(line);
		}
	}
	close(out_fd);
	return (0);
}

static int	expand_hdoc(char **hdoc, int in_fd)
{
	int		hdoc_fd;

	hdoc_fd = open(*hdoc, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (hdoc_fd == -1)
		return (-1);
	if (read_hdoc(in_fd, hdoc_fd) == -1)
		return (close(hdoc_fd), -1);
	close(hdoc_fd);
	return (0);
}

static int	exec_cat(char **env)
{
	char	*catcmd[2];
	pid_t	p;

	catcmd[0] = "cat";
	catcmd[1] = NULL;
	p = fork();
	if (p == -1)
		return (1);
	if (p == 0)
		execve("/usr/bin/cat", catcmd, env);
	wait(NULL);
	return (0);
}

static int	redirect_hdoc(char *hdoc, int fd, char **env, int type)
{
	int		hdoc_fd;

	hdoc_fd = open(hdoc, O_RDONLY);
	if (hdoc_fd == -1)
		return (-1);
	if (unlink(hdoc) == -1)
		return (close(hdoc_fd), -1);
	if (hdoc[ft_strlen(hdoc) - 1] == 'q' || type == 1)
	{
		if (dup2(hdoc_fd, fd) == -1)
			return (close(hdoc_fd), -1);
		close(hdoc_fd);
	}
	else
	{
		if (expand_hdoc(&hdoc, hdoc_fd) == -1)
			return (-1);
		close(hdoc_fd);
		return (redirect_hdoc(hdoc, fd, env, 1));
	}
	return (0);
}

int	get_hdoc(char *hdoc, int fd, char **env)
{
	int		fd_cpy;
	int		err;

	fd_cpy = dup(fd);
	if (fd_cpy == -1)
		return (-1);
	if (redirect_hdoc(hdoc, fd, env, 0) == -1)
		return (-1);
	err = exec_cat(env);
	if (dup2(fd_cpy, fd) == -1)
		return (close(fd_cpy), -1);
	close(fd_cpy);
	return (err);
}
