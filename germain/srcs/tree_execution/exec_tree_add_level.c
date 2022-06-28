/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree_add_level.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 10:59:39 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/28 12:13:15 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "astree.h"
#include "minishell.h"
#include "g_minishell.h"

pid_t	exec_tree_add_level(t_astree *node, int *pipe_in, int *pipe_out,
			t_clean *cleanable)
{
	pid_t	pid;
	int		n;
	int		i;

	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		return (-1);
	}
	if (pid == 0)
	{
		cleanable->depth = node->depth;
		i = 0;
		while (i < cleanable->n_pipes)
		{
			close(cleanable->pipe[2 * i]);
			close(cleanable->pipe[2 * i + 1]);
			i++;
		}
		cleanable->n_pipes = 0;
		n = count_wait_tree(node, cleanable->depth);
		pid = exec_tree(node, pipe_in, pipe_out, cleanable);
		close(pipe_out[0]);
		close(pipe_out[1]);
		clear_cleanable(cleanable);
		wait_all(n, pid);
		exit(get_status());
	}
	close(pipe_in[0]);
	close(pipe_in[1]);
	return (pid);
}