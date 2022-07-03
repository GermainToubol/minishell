/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_child.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 09:46:12 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/22 16:17:10 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "libft.h"
#include "parser.h"
#include "minishell.h"
#include "g_minishell.h"

static void	child_set_pipe(int *pipe_in, int *pipe_out);
static void	child_close_fds(t_parse *parse);
static int	check_path_exec(t_parse *parse);

void	run_child(t_parse *parse, t_list **env, int *pipe_in, int *pipe_out)
{
	char	**envp;

	child_set_pipe(pipe_in, pipe_out);
	if (do_redirect(parse) != 0)
		return ;
	if (get_exec_path(parse, env) != 0)
		return (child_close_fds(parse));
	if (check_path_exec(parse) != 0)
		return (child_close_fds(parse));
	envp = environment_format(*env);
	if (envp == NULL)
		return ;
	execve(parse->cmd->path_exec, parse->cmd->cmd, envp);
	perror("minishell: execve");
	child_close_fds(parse);
	ft_free_split(envp);
}

static void	child_set_pipe(int *pipe_in, int *pipe_out)
{
	if (pipe_in[0] != -2)
		close(pipe_in[1]);
	if (pipe_out[0] != -2)
		close(pipe_out[0]);
	if (pipe_in[0] != -2)
		dup2(pipe_in[0], STDIN_FILENO);
	if (pipe_out[0] != -2)
		dup2(pipe_out[1], STDOUT_FILENO);
	if (pipe_in[0] != -2)
		close(pipe_in[0]);
	if (pipe_out[0] != -2)
		close(pipe_out[1]);
}

static void	child_close_fds(t_parse *parse)
{
	int			i;
	t_redirect	**redirect;

	i = 0;
	redirect = parse->cmd->redirect;
	while (redirect != NULL && redirect[i] != NULL)
	{
		close(redirect[i]->fd);
		i++;
	}
}

static int	check_path_exec(t_parse *parse)
{
	struct stat file_stats;

	if (stat(parse->cmd->path_exec, &file_stats) == 0)
	{
		if (S_ISDIR(file_stats.st_mode) != 0)
		{
			ft_fprintf(2, "minishell: %s: Is a directory\n",
				parse->cmd->path_exec);
			return (set_status(126), 126);
		}
		return (0);
	}
	perror("minishell: stat");
	return (set_status(1), 1);
}
