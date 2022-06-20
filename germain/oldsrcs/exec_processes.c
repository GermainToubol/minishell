/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:36:20 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/20 10:12:32 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "parser.h"
#include "minishell.h"
#include "g_minishell.h"

static void	son_set_pipes(int *pipe_in, int *pipe_out);
static void	father_set_pipes(int *pipe_in);

pid_t	exec_process(t_parse *parse, char **env, int *pipe_in, int *pipe_out)
{
	pid_t	pid;
	t_cmd	*cmd;

	cmd = (t_cmd *)process->content;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid > 0)
	{
		extend_pid_list(pid);
		father_set_pipes(pipe_in);
		return (pid);
	}
	son_set_pipes(pipe_in, pipe_out);
	execve(cmd->path_exec, cmd->cmd, env);
	perror(cmd->cmd[0]);
	return (-2);
}

static void	son_set_pipes(int *pipe_in, int *pipe_out)
{
	if (pipe_in[0] >= 0)
	{
		close(pipe_in[1]);
		dup2(pipe_in[0], STDIN_FILENO);
		close(pipe_in[0]);
	}
	if (pipe_out[0] >= 0)
	{
		close(pipe_out[0]);
		dup2(pipe_out[1], STDOUT_FILENO);
		close(pipe_out[1]);
	}
}

static void	father_set_pipes(int *pipe_in)
{
	if (pipe_in[0] >= 0)
	{
		close(pipe_in[0]);
		close(pipe_in[1]);
	}
}
