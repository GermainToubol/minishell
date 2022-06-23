/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:40:00 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/23 18:26:18 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "astree.h"
#include "minishell.h"
#include "g_minishell.h"

pid_t	exec_tree_pipe(t_astree *node, int *pipe_in, int *pipe_out,
			t_clean *cleanable)
{
	pid_t	pid;
	int		tmp_pipe[2];

	pipe(tmp_pipe);
	pid = exec_tree(node->left, pipe_in, tmp_pipe, cleanable);
	if (pid == 0)
		return (pid);
	pid = exec_tree(node->right, tmp_pipe, pipe_out, cleanable);
	return (pid);
}
