/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_set_heredoc_content.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:25:54 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/10 13:24:47 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

static int	g_d_update_count(char *line, char *end_name, int *count);
static int	g_read_heredoc_return(char *line);

int	g_set_heredoc_content(char *end_name)
{
	int		len;
	int		count;
	char	*line;

	count = 0;
	len = ft_strlen(end_name);
	while (errno == 0)
	{
		line = get_next_line(0);
		if (line == NULL)
			continue ;
		if (ft_strncmp(line, end_name + count, len - count) == 0
			&& line[len - count] == '\n')
		{
			free(line);
			break ;
		}
		if (g_d_update_count(line, end_name, &count) != 0)
			continue ;
		ft_printf("%s", line);
		free(line);
	}
	return (g_read_heredoc_return(line));
}

static int	g_read_heredoc_return(char *line)
{
	if (errno != 0)
	{
		free(line);
		return (1);
	}
	return (0);
}

static int	g_d_update_count(char *line, char *end_name, int *count)
{
	if (ft_strncmp(line, end_name + *count, ft_strlen(line)) == 0)
	{
		*count += ft_strlen(line);
		free(line);
		return (1);
	}
	write(1, end_name, *count);
	*count = 0;
	return (0);
}
