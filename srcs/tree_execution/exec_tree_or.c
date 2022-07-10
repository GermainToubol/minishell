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

pid_t	exec_tree_or(t_astree *node, int *pipe_in, int *pipe_out,
			t_clean *cleanable)
{
	pid_t	pid;
	int		n;

	n = count_wait_tree(node->left, cleanable->depth);
	pid = exec_tree(node->left, pipe_in, pipe_out, cleanable);
	wait_all(n, pid);
	if (get_status() != 0 && get_status() != 130 && get_exit_state() == 0
		&& is_interupted() == 0)
	{
		n = count_wait_tree(node->right, cleanable->depth);
		pid = exec_tree(node->right, pipe_in, pipe_out, cleanable);
		wait_all(n, pid);
	}
	return (pid);
}
