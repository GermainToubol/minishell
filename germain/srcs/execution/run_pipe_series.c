/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe_series.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:58:08 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/22 16:26:27 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include "parser.h"
#include "utils.h"
#include "minishell.h"
#include "g_minishell.h"

static void	init_pfds(int (*pfd)[2], int *n_parse, pid_t *pid);
static void	clear_exec(t_parse **parse, int n_parse, t_list **env, pid_t pid);

int	run_pipe_series(t_parse **parse, t_list	**env)
{
	int		status;
	int		n_parse;
	pid_t	pid;
	int		pfd[2][2];

	init_pfds(pfd, n_parse, pid);
	while (parse[n_parse] != NULL && pid > 0)
	{
		status = 0;
		if (parse[n_parse]->type == PIPE)
		{
			n_parse++;
			continue ;
		}
		if (parse[n_parse + 1] != NULL && parse[n_parse + 1]->type == PIPE)
			status = do_bind_pipe(pfd[(n_parse / 2) % 2]);
		if (status == 0)
			pid = exec_process(parse[n_parse], env, pfd[(n_parse / 2 + 1) % 2],
					pfd[(n_parse / 2) % 2]);
		n_parse++;
	}
	clear_exec(parse, n_parse, env, pid);
	return (0);
}

static void	init_pfds(int (*pfd)[2], int *n_parse, pid_t *pid)
{
	*n_parse = 0;
	*pid = 1;
	pfd[0][0] = -2;
	pfd[0][1] = -2;
	pfd[1][0] = -2;
	pfd[1][1] = -2;
}

static void	clear_exec(t_parse **parse, int n_parse, t_list **env, pid_t pid)
{
	if (is_builtin(parse[n_parse - 1]->cmd->cmd[0]) && pid <= 0)
	{
		free_parse(parse);
		ft_lstclear(env, ft_freedico);
		exit(-pid);
	}
	free_parse(parse);
	if (pid == 0)
	{
		ft_lstclear(env, ft_freedico);
		exit(EXIT_FAILURE);
	}
	wait_all(n_parse / 2 + 1, pid);
}
