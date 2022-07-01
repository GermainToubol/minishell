/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree_or.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:02:44 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/27 13:03:08 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include "astree.h"
#include "utils.h"
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

static void	close_pipe(int *pfd);

pid_t	exec_tree_or(t_astree *node, int *pipe_in, int *pipe_out,
			t_clean *cleanable)
{
	pid_t	pid;
	int		tmp[2];
	int		n;

	tmp[0] = -2;
	tmp[1] = -2;
	if (pipe_in[0] != -2)
		tmp[0] = dup(pipe_in[0]);
	cleanable_add_pipe(cleanable, tmp);
	n = count_wait_tree(node->left, cleanable->depth);
	pid = exec_tree(node->left, pipe_in, pipe_out, cleanable);
	close_pipe(pipe_in);
	pipe_in[0] = tmp[0];
	wait_all(n, pid);
	if (get_status() != 0 && get_exit_state() == 0)
	{
		n = count_wait_tree(node->right, cleanable->depth);
		pid = exec_tree(node->right, pipe_in, pipe_out, cleanable);
		close(tmp[0]);
		wait_all(n, pid);
	}
	else
		close(tmp[0]);
	close_pipe(pipe_out);
	return (1);
}

static void	close_pipe(int *pfd)
{
	close(pfd[0]);
	close(pfd[1]);
}
