/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hdoc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 01:53:05 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/03 23:07:05 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "utils.h"
#include "libft.h"
#include "expand.h"
#include "parser.h"
#include <sys/types.h>
#include <sys/wait.h>

int	read_hdoc(int hdoc_fd, int out_fd)
{
	ssize_t	r;
	char	buffer[BUFFER_SIZE + 1];
	char	*line;
	char	**tmp;

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
			tmp = expand_var(buffer);
			if (!tmp)
				return (-1);
			line = ft_strnjoin(tmp, ' ');
			free(tmp);
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

int	close_hdoc(int fd, int fd_copy)
{
	if (dup2(fd_copy, fd) == -1)
		return (close(fd_copy), -1);
	close(fd_copy);
	return (0);
}

int	get_hdoc(t_parse *parse)
{
	int	i;

	if (parse->type != CMD || !parse->cmd || !parse->cmd->redirect)
		return (0);
	i = 0;
	while (parse->cmd->redirect[i] && parse->cmd->redirect[i]->io_r == HDOC)
		i++;
	if (parse->cmd->redirect[i])
		return (i);
	return (0);
}

int	dup_hdoc(char **env, t_parse *parse)
{
	int		fd_cpy;
	int		fd;
	char 	*file;
	int		i;

	i = get_hdoc(parse);
	if (i < 0)
		return (-1);
	file = parse->cmd->redirect[i]->file;
	fd = parse->cmd->redirect[i]->fd;
	fd_cpy = dup(fd);
	if (fd_cpy == -1)
		return (-1);
	if (redirect_hdoc(file, fd, env, 0) == -1)
		return (-1);
	return (fd_cpy);
}
