/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 22:01:05 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/18 14:03:23 by fmauguin         ###   ########.fr       */
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

void	astree_apply_prefix(t_astree *root)
{
	if (root->left)
		astree_apply_prefix(root->left);
	if (root->right)
		astree_apply_prefix(root->right);
	print_cmd(root);
}

t_astree	*create_node(t_parse *node)
{
	t_astree	*new;

	if (!node)
		return (NULL);
	new = ft_calloc(1, sizeof(t_astree));
	if (!new)
		return (display_error("Error allocation\n", 0), NULL);
	new->cmd = node;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

static void	fill_t_content(t_parse **parse, int depth,
		int start, t_int_help **i)
{
	(*i)->i = start;
	(*i)->min = start;
	(*i)->is_open = depth;
	(*i)->depth = depth;
	(*i)->is_done = 0;
	while (parse[(*i)->i] && (*i)->is_open >= depth)
	{
		if (parse[(*i)->i]->type == P_END)
			(*i)->is_open--;
		if (parse[(*i)->i]->type == P_START)
			(*i)->is_open++;
		(*i)->i++;
	}
	(*i)->max = (*i)->i;
	(*i)->i--;
}

t_int_help	*fill_t_int(t_parse **parse, int depth, int start)
{
	t_int_help	*i;

	i = ft_calloc(1, sizeof(t_int_help));
	if (!i)
		return (display_error("Error allocation\n", 0), NULL);
	fill_t_content(parse, depth, start, &i);
	while (i->i > i->min)
	{
		if (parse[i->i]->type == P_END)
			i->is_open++;
		if (parse[i->i]->type == P_START)
			i->is_open--;
		if (i->depth == i->is_open && (parse[i->i]->type == PIPE
				|| parse[i->i]->type == OR || parse[i->i]->type == AND))
			break ;
		i->i--;
	}
	return (i);
}
