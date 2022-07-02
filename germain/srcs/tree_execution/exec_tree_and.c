/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree_and.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:50:22 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/27 15:13:21 by gtoubol          ###   ########.fr       */
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

pid_t	exec_tree_and(t_astree *node, int *pipe_in, int *pipe_out,
			t_clean *cleanable)
{
	pid_t	pid;
	int		tmp[2] = {-2, -2};
	int		n;

	tmp[0] = -2;
	tmp[1] = -2;
	if (pipe_in[0] != -2)
		//tmp[0] = dup(pipe_in[0]);
		tmp[0] = dup2(pipe_in[0], 505);
	cleanable_add_pipe(cleanable, tmp);
	n = count_wait_tree(node->left, cleanable->depth);
	pid = exec_tree(node->left, pipe_in, pipe_out, cleanable);
	close_pipe(pipe_in);
	wait_all(n, pid);
	ft_fprintf(2, "Out pid: %d | int status: %d | $?: %d\n", pid, is_interupted(), get_status());
	pipe_in[0] = tmp[0];
	//cleanable->n_pipes -= 1;
	if (get_status() == 0 && get_exit_state() == 0 && is_interupted() == 0)
	{
		n = count_wait_tree(node->right, cleanable->depth);
		pid = exec_tree(node->right, pipe_in, pipe_out, cleanable);
		close_pipe(pipe_in);
		wait_all(n, pid);
	}
	else
		close(tmp[0]);
	close_pipe(pipe_out);
	return (pid);
}

static void	close_pipe(int *pfd)
{
	if (pfd[0] != -2)
		close(pfd[0]);
	if (pfd[1] != -2)
		close(pfd[1]);
}
