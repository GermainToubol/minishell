/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_set_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:53:00 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/09 14:19:52 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include "minishell.h"
#include "g_minishell.h"

/*
 * Set of the output pipe of a command:
 * If it is the last command or an output is set, does not create a new pipe.
 */

int	g_set_pipe(t_list *execline, int *pipe_fds)
{
	int		n;
	t_cmd	*cmd;

	cmd = (t_cmd *)execline->content;
	if (execline->next == NULL || cmd->output != NULL)
	{
		pipe_fds[0] = -2;
		pipe_fds[1] = -2;
		return (0);
	}
	n = pipe(pipe_fds);
	if (n != 0)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}
