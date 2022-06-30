/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rec_astree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 01:30:56 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/25 01:32:41 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astree.h"
#include "parser.h"

int	p_after(t_astree *node, t_parse **parse, t_int_help *i)
{
	t_int_help	*new;

	new = fill_t_int(parse, i->depth + 1, i->i + 1, 0);
	if (!new)
		return (1);
	node->right = create_node(parse[new->i], new->depth);
	if (!node->right)
		return (free(new), 1);
	if (run_tree(node->right, parse, new))
		return (free(new), 1);
	free(new);
	return (0);
}

int	p_before(t_astree *node, t_parse **parse, t_int_help *i)
{
	t_int_help	*new;

	new = fill_t_int(parse, i->depth + 1, i->min + 1, 0);
	if (!new)
		return (1);
	node->left = create_node(parse[new->i], new->depth);
	if (!node->left)
		return (free(new), 1);
	if (run_tree(node->left, parse, new))
		return (free(new), 1);
	free(new);
	return (0);
}

int	run_tree_left(t_astree *node, t_parse **parse, t_int_help *i)
{
	if (node->cmd->type == PIPE)
		i->i = get_next_left(parse, i, 1);
	else
		i->i = get_next_left(parse, i, 0);
	if (i->i == -1)
		return (0);
	if (parse[i->i]->type == P_END)
	{
		if (p_before(node, parse, i))
			return (1);
	}
	else
	{
		node->left = create_node(parse[i->i], i->depth);
		if (!node->left)
			return (1);
		if (parse[i->i]->type != CMD && run_tree(node->left, parse, i))
			return (1);
	}
	return (0);
}

int	run_tree_right(t_astree *node, t_parse **parse, t_int_help *i)
{
	t_int_help	*new;

	new = new_right(parse, i, i->i);
	if (!new)
		return (1);
	if (node->cmd->type == PIPE)
		new->i = get_next_right(parse, new, 1);
	else
		new->i = get_next_right(parse, new, 0);
	if (new->i == new->max)
		return (free(new), 0);
	if (parse[new->i]->type == P_START)
	{
		if (p_after(node, parse, new))
			return (free(new), 1);
	}
	else
	{
		node->right = create_node(parse[new->i], new->depth);
		if (!node->right)
			return (free(new), 1);
		if (parse[new->i]->type != CMD && run_tree(node->right, parse, new))
			return (free(new), 1);
	}
	return (free(new), 0);
}

int	run_tree(t_astree *node, t_parse **parse, t_int_help *i)
{
	int	index;

	index = i->i;
	if (parse[i->i]->type == CMD)
		return (0);
	if (run_tree_left(node, parse, i))
		return (1);
	i->i = index;
	if (run_tree_right(node, parse, i))
		return (1);
	return (0);
}
