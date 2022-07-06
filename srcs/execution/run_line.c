/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:38:31 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/27 15:48:27 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "utils.h"
#include "astree.h"
#include "minishell.h"
#include "g_minishell.h"

static int	do_exec_run(t_astree *root, t_parse **parse, t_list **env);

int	run_line(char *line, t_list **env)
{
	t_tokens	tokens;
	t_parse		**parse;
	t_astree	*root;

	if (lexer(line, &tokens) != 0)
		return (set_status(2), free(line), 1);
	free(line);
	parse = parser(&tokens);
	if (parse == NULL)
		return (1);
	if (create_astree(parse, &root))
		return (set_status(2), free_parse(parse), 1);
	return (do_exec_run(root, parse, env));
}

static int	do_exec_run(t_astree *root, t_parse **parse, t_list **env)
{
	run_tree_exec(root, parse, env);
	return (0);
}
