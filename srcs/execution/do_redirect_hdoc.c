/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redirect_hdoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 13:38:35 by gtoubol           #+#    #+#             */
/*   Updated: 2022/07/04 15:24:00 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "libft.h"
#include "expand.h"
#include "minishell.h"
#include "g_minishell.h"

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

static int	redirect_hdoc(char *hdoc, int fd, int type)
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
		return (redirect_hdoc(hdoc, fd, 1));
	}
	return (0);
}

int	do_redirect_hdoc(char *filename, int target_fd)
{
	return (redirect_hdoc(filename, target_fd, 0));
}
