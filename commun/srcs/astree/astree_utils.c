/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 22:01:05 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/24 18:02:19 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astree.h"
#include "parser.h"
#include "minishell.h"
#include "utils.h"

void	print_cmd(t_astree *root)
{
	const char	*e_type[] = {"CMD", "PIPE", "OR", "AND", "P_START", "P_END"};
	const char	*e_colors[] = {"\x1b[32m", "\x1b[33m", "\x1b[36m", "\x1b[34m",
		"\x1b[35m", "\x1b[31m"};
	int			type;

	type = root->cmd->type;
	if (type == CMD)
		type = 0;
	else
		type -= 4;
	ft_printf("\n\t%s%s\x1b[0m", e_colors[type], e_type[type]);
	if (!root->cmd->cmd)
		ft_printf("\n");
	else
		print_node(root->cmd->cmd);
}

void	free_tree(t_astree *root)
{
	if (!root)
		return ;
	if (!root->cmd)
		free_parse(&root->cmd);
	free(root);
}

void	astree_apply_suffix(t_astree *root, void (*f)(t_astree *))
{
	if (root->left)
		astree_apply_suffix(root->left, f);
	if (root->right)
		astree_apply_suffix(root->right, f);
	f(root);
}

t_astree	*create_node(t_parse *node, int depth)
{
	t_astree	*new;

	if (!node)
		return (NULL);
	new = ft_calloc(1, sizeof(t_astree));
	if (!new)
		return (display_error("Error allocation\n", 0), NULL);
	new->cmd = node;
	new->depth = depth;
	new->left = NULL;
	new->right = NULL;
	return (new);
}
