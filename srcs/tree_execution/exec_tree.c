/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:21:00 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/27 11:03:36 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "astree.h"
#include "minishell.h"
#include "g_minishell.h"

pid_t	exec_tree(t_astree *node, int *pipe_in, int *pipe_out,
			t_clean *cleanable)
{
	if (node->depth > cleanable->depth)
		return (exec_tree_add_level(node, pipe_in, pipe_out, cleanable));
	if (node->cmd->type == CMD)
		return (exec_tree_cmd(node->cmd, pipe_in, pipe_out, cleanable));
	if (node->cmd->type == PIPE)
		return (exec_tree_pipe(node, pipe_in, pipe_out, cleanable));
	if (node->cmd->type == AND)
		return (exec_tree_and(node, pipe_in, pipe_out, cleanable));
	if (node->cmd->type == OR)
		return (exec_tree_or(node, pipe_in, pipe_out, cleanable));
	return (-1);
}
