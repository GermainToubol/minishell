/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hdoc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 22:50:53 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/30 01:23:06 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	tmp_filename_loop(int i, char *filename)
{
	while (filename[i] == '9')
		filename[i--] = '0';
	if (i < 13)
		return (1);
	while (ft_isdigit(filename[i]))
		i++;
	i--;
	filename[i] = filename[i] + 1;
	return (0);
}

char	*tmp_filename(void)
{
	char	tmp_file[21];
	int		i;
	char	*ret;

	i = -1;
	ret = "/tmp/sh-thd-00000000";
	while (ret[++i])
		tmp_file[i] = ret[i];
	tmp_file[i--] = 0;
	while (!access(tmp_file, F_OK))
		if (tmp_filename_loop(i, tmp_file))
			return (NULL);
	ret = ft_strdup(tmp_file);
	if (!ret)
		display_error("Error allocation\n", 0);
	return (ret);
}

char	*tmp_filename_q(void)
{
	char	tmp_file[22];
	int		i;
	char	*ret;

	i = -1;
	ret = "/tmp/sh-thd-00000000q";
	while (ret[++i])
		tmp_file[i] = ret[i];
	tmp_file[i--] = 0;
	i--;
	while (!access(tmp_file, F_OK))
		if (tmp_filename_loop(i, tmp_file))
			return (NULL);
	ret = ft_strdup(tmp_file);
	if (!ret)
		display_error("Error allocation\n", 0);
	return (ret);
}

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
		if (!ft_strcmp(line, eof))
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
		return (free(hdoc_name), 1);
	dup2(hdoc_fd, 4);
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
		return (free(hdoc_name), 1);
	dup2(hdoc_fd, 4);
	eof = quotes_hdoc(*hdoc);
	ft_printf("eof %s\n", eof);
	if (create_hdoc_loop(eof))
		return (free(eof), 1);
	free(eof);
	close(hdoc_fd);
	free(*hdoc);
	*hdoc = hdoc_name;
	return (0);
}

int	get_hdoc(char **hdoc)
{
	if (ft_strchr(*hdoc, '"') || ft_strchr(*hdoc, '\''))
	{
		if (create_hdoc_q(hdoc))
			return (1);
	}
	else
	{
		if (create_hdoc(hdoc))
			return (1);
	}
	return (0);
}
