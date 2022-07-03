/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:20:09 by gtoubol           #+#    #+#             */
/*   Updated: 2022/05/31 17:32:51 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

static size_t	gnl_nl_place(char *str, size_t size);
static char		*gnl_read_to_newline(int fd, t_buffer *buffer, size_t *size);
static size_t	gnl_join(char **dest, size_t size_d, char *src, size_t size_s);
static char		*gnl_update_newline_buffer(
					char *src,
					size_t size,
					t_buffer *buffer);

char	*get_next_line_fds(int fd)
{
	static t_buffer	buffer_list[MAX_FDS] = {{0, 0, {0}}};
	t_buffer		*current_buffer;
	char			*newline;
	size_t			size;

	if (fd < 0)
		return (NULL);
	current_buffer = gnl_get_buffer(fd, buffer_list);
	if (current_buffer == NULL)
		return (NULL);
	size = 0;
	newline = NULL;
	newline = gnl_read_to_newline(fd, current_buffer, &size);
	if (newline)
		newline = gnl_update_newline_buffer(newline, size, current_buffer);
	return (newline);
}

static size_t	gnl_nl_place(char *str, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

static char	*gnl_read_to_newline(int fd, t_buffer *buffer, size_t *size)
{
	char	*newline;
	ssize_t	re;

	newline = NULL;
	*size = gnl_join(&newline, 0, buffer->buffer, buffer->size);
	if (buffer->size && newline == NULL)
		return (NULL);
	re = 1;
	while (re && !gnl_nl_place(newline, *size))
	{
		re = read(fd, buffer->buffer, BUFFER_SIZE);
		if (re < 0)
		{
			free(newline);
			return (NULL);
		}
		*size = gnl_join(&newline, *size, buffer->buffer, re);
		if (!newline)
			return (NULL);
	}
	return (newline);
}

static size_t	gnl_join(char **dest, size_t size_d, char *src, size_t size_s)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	tmp = NULL;
	if (size_d + size_s != 0)
		tmp = ft_calloc(size_d + size_s, sizeof(*tmp));
	if (!tmp)
	{
		free(*dest);
		*dest = NULL;
		return (0);
	}
	i = -1;
	while (++i < size_d)
		tmp[i] = (*dest)[i];
	j = -1;
	while (++j < size_s)
		tmp[i + j] = src[j];
	free(*dest);
	*dest = tmp;
	return (i + j);
}

static char	*gnl_update_newline_buffer(char *src, size_t size, t_buffer *buffer)
{
	char	*newline;
	size_t	position;
	size_t	i;

	newline = NULL;
	position = gnl_nl_place(src, size);
	i = 0;
	while (position && position + i < size)
	{
		buffer->buffer[i] = src[position + i];
		i++;
	}
	buffer->size = i;
	if (position)
		size = gnl_join(&newline, 0, src, position);
	else
		size = gnl_join(&newline, 0, src, size);
	free(src);
	if (!newline)
		return (NULL);
	gnl_join(&newline, size, "\0", 1);
	return (newline);
}
