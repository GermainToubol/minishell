/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_session.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:10:53 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/23 11:11:32 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <readline/readline.h>
#include <readline/history.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "g_minishell.h"

static int	do_execution(t_list **env);

int	interactive_session(t_list	**env)
{
	struct sigaction	sa;
	int					is_done;

	is_done = 0;
	if (isatty(2))
		rl_outstream = stderr;
	if (init_signal_interactive(&sa) != 0)
	{
		perror("minishell: signal init");
		return (1);
	}
	rl_clear_history();
	while (is_done == 0)
	{
		is_done = do_execution(env);
	}
	rl_clear_history();
	close(0);
	close(1);
	close(2);
	return (0);
}

static int	do_execution(t_list **env)
{
	char	*line;
	int		re;

	line = readline(PROMPT_NAME);
	if (line == NULL || ft_strcmp(line, "exit") == 0)
	{
		free(line);
		write(2, "exit\n", 5);
		return (1);
	}
	if (ft_strcmp(line, "") == 0)
	{
		free(line);
		return (0);
	}
	add_history(line);
	re = run_line(line, env);
	(void)re;
	return (0);
}
