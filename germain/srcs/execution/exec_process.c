/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 09:24:46 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/23 10:56:56 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "libft.h"
#include "parser.h"
#include "minishell.h"
#include "g_minishell.h"

pid_t	exec_process(t_parse *parse, t_list **env, int *pipe_in, int *pipe_out)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror("minishell: fork");
	if (pid == 0)
	{
		if (is_builtin(parse->cmd->cmd[0]))
			return (-run_builtin(parse, env, pipe_in, pipe_out));
		run_child(parse, env, pipe_in, pipe_out);
	}
	if (pid > 0)
		run_parent(pipe_in);
	return (pid);
}
