/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 09:24:46 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/28 11:33:19 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "libft.h"
#include "parser.h"
#include "minishell.h"
#include "g_minishell.h"

pid_t	exec_process(t_parse *parse, t_clean *cleanable, int *pipe_in, int *pipe_out)
{
	pid_t	pid;
	int		i;

	if (is_builtin(parse))
		return (-run_builtin(parse, cleanable->env, pipe_in, pipe_out));
	pid = fork();
	if (pid < 0)
		perror("minishell: fork");
	if (pid == 0)
	{
		i = 0;
		while (i < cleanable->n_pipes)
		{
			close(cleanable->pipe[2 * i]);
			close(cleanable->pipe[2 * i + 1]);
			i++;
		}
		cleanable->n_pipes = 0;
		run_child(parse, cleanable->env, pipe_in, pipe_out);
		exit(0);
	}
	if (pid > 0)
		run_parent(pipe_in);
	return (pid);
}
