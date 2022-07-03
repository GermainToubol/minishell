/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:21:52 by gtoubol           #+#    #+#             */
/*   Updated: 2022/05/16 17:15:42 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_buffer	*gnl_get_buffer(int fd, t_buffer *buffers)
{
	int	new_fd;
	int	i;

	i = 0;
	new_fd = fd % MAX_FDS;
	if (buffers[new_fd].fd == fd)
		return (buffers + new_fd);
	if (buffers[new_fd].fd == 0)
	{
		buffers[new_fd].fd = fd;
		return (buffers + new_fd);
	}
	while (buffers[new_fd].fd != fd)
	{
		if (buffers[new_fd].fd == 0 && new_fd != 0)
		{
			buffers[new_fd].fd = fd;
			return (buffers + new_fd);
		}
		if (i == MAX_FDS)
			return (NULL);
		i++;
		new_fd = (new_fd + 1) % MAX_FDS;
	}
	return (buffers + new_fd);
}
