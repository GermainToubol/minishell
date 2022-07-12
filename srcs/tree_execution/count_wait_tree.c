/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_wait_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:42:36 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/28 10:35:48 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "astree.h"
#include "parser.h"
#include "minishell.h"
#include "g_minishell.h"

int	count_wait_tree(t_astree *root, int depth)
{
	int	tmp1;
	int	tmp2;

	if (root->depth > depth)
		return (1);
	if (root->cmd->type == CMD && is_builtin(root->cmd))
		return (0);
	if (root->cmd->type == CMD)
		return (1);
	if (root->cmd->type == AND || root->cmd->type == OR)
		return (0);
	else if (root->cmd->type == PIPE)
		return (2);
	return (0);
}
