/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 09:48:12 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/10 16:03:35 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

/*
  1- Find the list of the heredocs
  2- Get the heredocs contents using malloc.
  3- replace by files.
  4. run and unlink.
*/

int	main(int argc, char **argv, char **env)
{
	t_list	*execline;
	t_list	*heredoc_list;
	int		exit_status;

	(void)argc;
	(void)argv;
	execline = tmp_init_exec();
	heredoc_list = g_init_heredocs(execline);
	exit_status = g_run_pipe_series(execline, &heredoc_list, env);
	g_clear_heredocs(&heredoc_list);
	return (exit_status);
}
