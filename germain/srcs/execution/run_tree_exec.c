/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 13:29:58 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/27 15:04:53 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "libft.h"
#include "parser.h"
#include "utils.h"
#include "astree.h"
#include "minishell.h"
#include "g_minishell.h"

static void	init_pfds(int (*pfd)[2], pid_t *pid);

int	run_tree_exec(t_astree *root, t_parse **parse, t_list **env)
{
	pid_t	pid;
	int		n;
	int		pfd[2][2];
	t_clean	cleanable;

	init_pfds(pfd, &pid);
	cleanable.env = env;
	cleanable.root = root;
	cleanable.parse = parse;
	cleanable.depth = 0;
	n = count_wait_tree(root, 0);
	pid = exec_tree(root, pfd[0], pfd[1], &cleanable);
	astree_apply_suffix(root, free_tree);
	free_parse(parse);
	if (pid == 0)
	{
		ft_lstclear(env, ft_freedico);
		exit(EXIT_FAILURE);
	}
	wait_all(n, pid);
	return (0);
}

static void	init_pfds(int (*pfd)[2], pid_t *pid)
{
	*pid = 1;
	pfd[0][0] = -2;
	pfd[0][1] = -2;
	pfd[1][0] = -2;
	pfd[1][1] = -2;
}
