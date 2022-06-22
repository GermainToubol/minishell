/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:38:31 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/22 16:20:43 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "utils.h"
#include "minishell.h"
#include "g_minishell.h"

static int	do_exec_run(t_parse **parse, t_list **env);

int	run_line(char *line, t_list **env)
{
	t_tokens	tokens;
	t_parse		**parse;

	if (lexer(line, &tokens) != 0)
	{
		free(line);
		return (1);
	}
	free(line);
	parse = parser(&tokens);
	if (parse == NULL)
		return (1);
	if (parse[0]->type == CMD && parse[0]->cmd->cmd[0] == NULL)
	{
		free_parse(parse);
		return (0);
	}
	return (do_exec_run(parse, env));
}

static int	do_exec_run(t_parse **parse, t_list **env)
{
	int	status;

	if (parse[0] != NULL && parse[1] == NULL)
	{
		if (is_builtin(parse[0]->cmd->cmd[0]))
		{
			status = run_builtin(parse[0], env, (int [2]){-2, -2},
					(int [2]){-2, -2});
			free_parse(parse);
			return (status);
		}
	}
	run_pipe_series(parse, env);
	return (0);
}
