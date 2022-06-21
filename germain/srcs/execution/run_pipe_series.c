/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe_series.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:58:08 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/20 17:51:03 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include "parser.h"
#include "minishell.h"
#include "g_minishell.h"

int	run_pipe_series(t_parse **parse, t_list	**env)
{
	//int		pfd[2][2];
	//int		n_process;
	int		n_parse;
	pid_t	pid;

	//n_process = 0;
	(void)env;
	n_parse = 0;
	pid = 1;
	while (parse[n_parse] != NULL && pid > 0)
	{
		if (parse[n_parse]->type == CMD)
			do_redirect(parse[n_parse]);
		n_parse++;
	}
	if (pid <= 0)
		return (1);
	return (0);
}
