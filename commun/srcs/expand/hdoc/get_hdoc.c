/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hdoc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 22:50:53 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/30 00:01:33 by fmauguin         ###   ########.fr       */
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

char	*tmp_filename(void)
{
	char	tmp_file[21];
	int		i;
	char	count;
	char	*ret;

	i = -1;
	count = '0';
	ret = "/tmp/sh-thd-00000000";
	while (ret[++i])
		tmp_file[i] = ret[i];
	tmp_file[i--] = '\0';
	while (!access(tmp_file, F_OK))
	{
		tmp_file[i] = ++count;
		if (count > '9' && i--)
			count = 0;
		if (i < 13)
			return (NULL);
	}
	ret = ft_strdup(tmp_file);
	if (!ret)
		display_error("Error allocation\n", 0);
	return (ret);
}

int	get_hdoc(char **hdoc)
{
	char	*line;
	char	*hdoc_name;
	int		hdoc_fd;

	hdoc_name = tmp_filename();
	if (!hdoc)
		return (1);
	hdoc_fd = open(hdoc_name, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (hdoc_fd == -1)
		return (free(hdoc_name), 1);
	ft_printf("here\n");
	dup2(hdoc_fd, 4);
	line = NULL;
	while (ft_strcmp(line, *hdoc))
	{
		free(line);
		line = get_next_line(0);
		if (!line)
			return (free(hdoc_name), 1);
		write (4, line, ft_strlen(line));
	}
	close(hdoc_fd);
	free(*hdoc);
	*hdoc = hdoc_name;
	return (0);
}
