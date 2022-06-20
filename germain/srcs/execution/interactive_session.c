/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_session.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:10:53 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/20 18:03:51 by gtoubol          ###   ########.fr       */
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

int interactive_session(t_list	**env)
{
	struct sigaction	sa;
	int					is_done;

	is_done = 0;
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
	return (0);
}

static int	do_execution(t_list **env)
{
	static int a = 0;
	char	*line;
	int		re;

	(void)env;
	if (a == 0)
		line = "14<Makefile >>test >lapin";//readline(PROMPT_NAME);
	else
		line = NULL;
	a++;
	if (line == NULL || ft_strcmp(line, "exit") == 0)
	{
		//free(line);
		write(1, "exit\n", 5);
		return (1);
	}
	//add_history(line);
	//rl_redisplay();
	re = run_line(line, env);
	//rl_on_new_line();
	//free(line);
	(void)re;
	return (0);
}
