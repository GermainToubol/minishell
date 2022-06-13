/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_session.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:33:07 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/13 16:41:53 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <readline/readline.h>
#include <readline/history.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "minishell.h"
#include "g_minishell.h"

int	interactive_session(char **env)
{
	char	*line;
	int		is_done;

	is_done = 0;
	rl_clear_history();
	while (is_done == 0)
	{
		line = readline("gms> ");
		if (line == NULL)
		{
			is_done = 1;
			continue ;
		}
		add_history(line);
		non_interactive_session(line, env);
		rl_redisplay();
		rl_on_new_line();
		free(line);
	}
	return (0);
}
