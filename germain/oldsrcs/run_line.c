/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:33:43 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/20 09:23:10 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "utils.h"
#include "minishell.h"
#include "g_minishell.h"

void	run_line(char *line, char **env)
{
	t_tokens	tokens;
	t_parse		**parse;

	(void)env;
	if (lexer(line, &tokens))
	{
		free(line);
		return ;
	}
	print_lexer(line, &tokens);
	free(line);
	parse = parser(&tokens);
	if (!parse)
		return ;
	run_pipe_series(parse, env);
	free_parse(parse);
}
