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

static void	close_pipes(int *pipe_fds);

pid_t	exec_tree_add_level(t_astree *node, int *pipe_in, int *pipe_out,
			t_clean *cleanable)
{
	pid_t	pid;
	int		n;

	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		return (-1);
	}
	if (pid == 0)
	{
		cleanable->depth = node->depth;
		while (cleanable->n_pipes > 0)
			cleanable_pop_pipe(cleanable);
		n = count_wait_tree(node, cleanable->depth);
		pid = exec_tree(node, pipe_in, pipe_out, cleanable);
		close_pipes(pipe_out);
		clear_cleanable(cleanable);
		wait_all(n, pid);
		exit(get_status());
	}
	close_pipes(pipe_in);
	if (pid_extend_list(pid))
		return (-1);
	return (pid);
}

static void	close_pipes(int *pipe_fds)
{
	if (pipe_fds[0] != -2)
	{
		close(pipe_fds[0]);
		close(pipe_fds[1]);
	}
}
