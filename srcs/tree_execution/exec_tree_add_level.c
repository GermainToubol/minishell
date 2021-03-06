/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree_add_level.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 10:59:39 by gtoubol           #+#    #+#             */
/*   Updated: 2022/07/04 18:06:21 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "astree.h"
#include "minishell.h"
#include "g_minishell.h"

static void	close_pipes(int *pipe_fds);
static int	set_pipes(int *pipe_in, int *pipe_out);

pid_t	exec_tree_add_level(t_astree *node, int *pipe_in, int *pipe_out,
			t_clean *cleanable)
{
	pid_t	pid;
	int		n;

	pid = fork();
	if (pid < 0)
		return (perror("minishell: fork"), set_status(-1), -1);
	if (pid != 0 && pid_extend_list(pid))
		return (close_pipes(pipe_in), unset_father(), set_status(-1), -1);
	else if (pid != 0)
		return (close_pipes(pipe_in), unset_father(), pid);
	pid_clear_list();
	unset_father();
	cleanable->depth = node->depth;
	cleanble_close_pipes(cleanable);
	if (set_pipes(pipe_in, pipe_out) < 0)
		return (set_status(1), -1);
	n = count_wait_tree(node, cleanable->depth);
	pid = exec_tree(node, (int [2]){-2, -2}, (int [2]){-2, -2}, cleanable);
	if (pid == 0)
		return (0);
	wait_all(n, pid);
	clear_cleanable(cleanable);
	close_pipes((int [2]){0, 1});
	exit(get_status());
	return (0);
}

static void	close_pipes(int *pipe_fds)
{
	if (pipe_fds[0] != -2)
	{
		close(pipe_fds[0]);
		close(pipe_fds[1]);
	}
}

static int	set_pipes(int *pipe_in, int *pipe_out)
{
	int	status;

	status = 1;
	if (pipe_in[0] != -2)
	{
		close(pipe_in[1]);
		status = dup2(pipe_in[0], STDIN_FILENO);
		close(pipe_in[0]);
	}
	if (pipe_out[0] != -2 && status >= 0)
	{
		close(pipe_out[0]);
		status = dup2(pipe_out[1], STDOUT_FILENO);
		close(pipe_out[1]);
	}
	if (status < 0)
		perror("minishell: dup");
	return (status);
}
