/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:13:16 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/22 11:28:09 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "parser.h"
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

static void	*get_redirect_function(t_eio io_r);
static int	redirect_in(char *filename, int target_fd);
static int	redirect_out(char *filename, int target_fd);
static int	redirect_append(char *filename, int target_fd);

int	do_redirect(t_parse *parse)
{
	int			i;
	t_redirect	**redirect;
	int			(*f)(char *, int);

	i = 0;
	redirect = parse->cmd->redirect;
	while (redirect != NULL && redirect[i] != NULL)
	{
		f = get_redirect_function(redirect[i]->io_r);
		if (f == NULL)
		{
			i++;
			continue ;
		}
		if (f(redirect[i]->file, redirect[i]->fd) != 0)
			return (set_status(1), 1);
		i++;
	}
	return (0);
}

static void	*get_redirect_function(t_eio io_r)
{
	if (io_r == IN)
		return (redirect_in);
	if (io_r == OUT)
		return (redirect_out);
	if (io_r == APP)
		return (redirect_append);
	return (NULL);
}

static int	redirect_in(char *filename, int target_fd)
{
	int	fd;

	fd = open(filename, O_RDONLY, 0400);
	if (fd < 0)
	{
		ft_fprintf(2, "%s: %s: %s\n", "minishell", filename, strerror(errno));
		return (1);
	}
	if (dup2(fd, target_fd) != target_fd)
	{
		close(fd);
		ft_fprintf(2, "%s: %d: %s\n", "minishell", target_fd, strerror(errno));
		return (1);
	}
	close(fd);
	return (0);
}

static int	redirect_out(char *filename, int target_fd)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_fprintf(2, "%s: %s: %s\n", "minishell", filename, strerror(errno));
		return (1);
	}
	if (dup2(fd, target_fd) != target_fd)
	{
		close(fd);
		ft_fprintf(2, "%s: %d: %s\n", "minishell", target_fd, strerror(errno));
		return (1);
	}
	close(fd);
	return (0);
}

static int	redirect_append(char *filename, int target_fd)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_fprintf(2, "%s: %s: %s\n", "minishell", filename, strerror(errno));
		return (1);
	}
	if (dup2(fd, target_fd) != target_fd)
	{
		close(fd);
		ft_fprintf(2, "%s: %d: %s\n", "minishell", target_fd, strerror(errno));
		return (1);
	}
	close(fd);
	return (0);
}
