/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 22:01:05 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/17 22:14:45 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astree.h"
#include "parser.h"
#include "minishell.h"

void	print_cmd(void *data)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)data;
	print_node(cmd);
}

void	astree_apply_prefix(t_astree *root)
{
	const char	*e_type[] = {"CMD", "PIPE", "OR", "AND", "P_START", "P_END"};
	const char	*e_colors[] = {"\x1b[32m", "\x1b[33m", "\x1b[36m", "\x1b[34m",
		"\x1b[35m", "\x1b[31m"};
	int			type;

	if (root->left)
		astree_apply_prefix(root->left);
	type = root->cmd->type;
	if (type == CMD)
		type = 0;
	else
		type -= 4;
	ft_printf("\n\t%s%s\x1b[0m", e_colors[type], e_type[type]);
	print_node(root->cmd->cmd);
	if (root->right)
		astree_apply_prefix(root->right);
}
