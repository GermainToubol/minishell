/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:31:13 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/28 09:34:01 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "astree.h"
#include "minishell.h"
#include "g_minishell.h"
#include "libft.h"

pid_t	exec_tree_cmd(t_parse *parse, int *pipe_in, int *pipe_out,
			t_clean *cleanable)
{
	pid_t	pid;

	pid = exec_process(parse, cleanable, pipe_in, pipe_out);
	if (pid < -500)
	{
		clear_cleanable(cleanable);
		exit(2);
	}
	return (pid);
}
