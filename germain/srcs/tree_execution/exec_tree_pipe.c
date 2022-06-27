/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:40:00 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/27 15:20:22 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "astree.h"
#include "minishell.h"
#include "g_minishell.h"

static int	set_builtin_level_left(t_astree *node);
static int	set_builtin_level_right(t_astree *node);

pid_t	exec_tree_pipe(t_astree *node, int *pipe_in, int *pipe_out,
			t_clean *cleanable)
{
	pid_t	pid;
	int		tmp_pipe[2];
	int		builtin_level;

	pipe(tmp_pipe);
	builtin_level = set_builtin_level_left(node);
	if (builtin_level == 1)
		cleanable->depth -= 1;
	pid = exec_tree(node->left, pipe_in, tmp_pipe, cleanable);
	if (builtin_level == 1)
		cleanable->depth += 1;
	if (pid == 0)
		return (pid);
	builtin_level = set_builtin_level_right(node);
	if (builtin_level == 1)
		cleanable->depth -= 1;
	pid = exec_tree(node->right, tmp_pipe, pipe_out, cleanable);
	if (builtin_level == 1)
		cleanable->depth += 1;
	if (pid == 0)
		return (pid);
	return (pid);
}

static int	set_builtin_level_left(t_astree *node)
{
	if (node->left->depth == node->depth && is_builtin(node->left->cmd))
		return (1);
	return (0);
}

static int	set_builtin_level_right(t_astree *node)
{
	if (node->right->depth == node->depth && is_builtin(node->right->cmd))
		return (1);
	return (0);
}
