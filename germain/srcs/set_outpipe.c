/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_outpipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:53:15 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/14 16:02:14 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include "minishell.h"
#include "g_minishell.h"

int	set_outpipe(t_list *execline, int *pipe_fds)
{
	int		n;
	t_cmd	*cmd;

	cmd = (t_cmd *)execline->content;
	if (execline->next == NULL || cmd->outputs != NULL)
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
