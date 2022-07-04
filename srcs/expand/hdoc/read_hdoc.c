/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_hdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 02:18:03 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/04 02:23:29 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "expand.h"
#include "utils.h"

static int	read_hdoc_content(int out_fd, char *buffer, ssize_t r)
{
	char	**tmp;
	char	*line;

	if (!ft_strchr(buffer, '$'))
		write (out_fd, buffer, r);
	else
	{
		tmp = expand_var(buffer);
		if (!tmp)
			return (1);
		line = ft_strnjoin(tmp, ' ');
		free(tmp);
		if (line)
			write (out_fd, line, ft_strlen(line));
		free(line);
	}
	return (0);
}

int	read_hdoc(int hdoc_fd, int out_fd)
{
	ssize_t	r;
	char	buffer[BUFFER_SIZE + 1];

	r = 1;
	while (r)
	{
		r = read(hdoc_fd, &buffer, BUFFER_SIZE);
		if (r == -1)
			return (-1);
		if (r == 0)
			break ;
		buffer[r] = '\0';
		if (read_hdoc_content(out_fd, buffer, r))
			return (-1);
	}
	close(out_fd);
	return (0);
}
