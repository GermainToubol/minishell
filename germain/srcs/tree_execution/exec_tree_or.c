/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree_or.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:02:44 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/23 18:13:29 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include "astree.h"
#include "minishell.h"
#include "g_minishell.h"

pid_t	exec_tree_or(t_astree *node, int *pipe_in, int *pipe_out,
			t_clean *cleanable)
{
	pid_t	pid;
	int		n;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (pid);
	}
	if (pid > 0)
		return (pid);
	n = count_wait_tree(node->left);
	pid = exec_tree(node->left, pipe_in, pipe_out, cleanable);
	status = wait_all(n, pid);
	status = 1;
	if (status != 0)
	{
		n = count_wait_tree(node->right);
		pid = exec_tree(node->right, pipe_in, pipe_out, cleanable);
		wait_all(n, pid);
	}
	return (0);
}
