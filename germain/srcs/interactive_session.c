/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_session.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:33:07 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/14 13:35:59 by gtoubol          ###   ########.fr       */
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

static int	do_execution(char **env);

int	interactive_session(char **env)
{
	struct sigaction	sa;
	int					is_done;

	is_done = 0;
	if (init_signal_interactive(&sa) != 0)
	{
		perror("minishell : initialisation : ");
		return (0);
	}
	rl_clear_history();
	while (is_done == 0)
	{
		is_done = do_execution(env);
	}
	return (0);
}

static int	do_execution(char **env)
{
	char	*line;

	line = readline("gms> ");
	if (line == NULL || ft_strcmp(line, "exit") == 0)
	{
		free(line);
		write(1, "exit\n", 5);
		return (1);
	}
	add_history(line);
	exec_processes(line);
	rl_redisplay();
	rl_on_new_line();
	free(line);
	return (0);
}
