/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:38:31 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/20 18:06:27 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "utils.h"
#include "minishell.h"
#include "g_minishell.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int	run_line(char *line, t_list **env)
{
	t_tokens	tokens;
	t_parse		**parse;

	(void)env;
	if (lexer(line, &tokens) != 0)
		return (1);
	parse = parser(&tokens);
	if (parse == NULL)
		return (1);
	run_pipe_series(parse, env);
	free_parse(parse);
	return (0);
}
