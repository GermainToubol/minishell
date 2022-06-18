/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_astree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:09:36 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/18 14:09:48 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astree.h"
#include "utils.h"

int	p_after(t_astree *node, t_parse **parse, t_int_help *i)
{
	t_int_help	*new;

	new = fill_t_int(parse, i->depth + 1, i->i + 1);
	if (!new)
		return (1);
	node->right = create_node(parse[new->i]);
	if (!node->right)
		return (1);
	new->i--;
	(i->i) = new->max;
	i->is_open = i->depth;
	if (run_tree(node->right, parse, new))
		return (free(new), 1);
	free(new);
	(i->i)++;
	return (0);
}

int	p_before(t_astree *node, t_parse **parse, t_int_help *i)
{
	t_int_help	*new;

	new = fill_t_int(parse, i->depth + 1, i->min + 1);
	if (!new)
		return (1);
	node->left = create_node(parse[new->i]);
	if (!node->left)
		return (1);
	new->i--;
	if (run_tree(node->left, parse, new))
		return (free(new), 1);
	(i->i) = new->max;
	i->is_open = i->depth;
	free(new);
	i->is_done = 1;
	return (0);
}

int	base_tree(t_astree *node, t_parse **parse, t_int_help *i)
{
	if (i->is_done)
	{
		if (i->i < i->max && (parse[i->i]->type == PIPE
				|| parse[i->i]->type == OR || parse[i->i]->type == AND))
			(i->i)++;
		if (parse[i->i]->type == P_START)
		{
			i->is_open++;
			if (i->is_open == i->depth + 1)
				if (p_after(node, parse, i))
					return (1);
		}
		else if (i->i < i->max && i->is_open == i->depth
			&& parse[i->i]->type == CMD)
		{
			node->right = create_node(parse[i->i]);
			if (!node->right)
				return (1);
			(i->i)++;
		}
	}
	return (0);
}

int	run_tree_content(t_astree *node, t_parse **parse, t_int_help *i)
{
	if (i->i == i->min && parse[i->i]->type == CMD)
	{
		node->left = create_node(parse[i->i]);
		if (!node->left)
			return (1);
		i->is_done = 1;
		(i->i)++;
	}
	else if (i->i == i->min && parse[i->i]->type == P_START)
	{
		if (p_before(node, parse, i))
			return (1);
	}
	else if (i->is_open == i->depth)
	{
		node->left = create_node(parse[i->i]);
		if (!node->left)
			return (1);
		(i->i)--;
		if (run_tree(node->left, parse, i))
			return (1);
	}
	return (0);
}

int	run_tree(t_astree *node, t_parse **parse, t_int_help *i)
{
	if (!i->is_done)
	{
		while (i->i > i->min)
		{
			if (parse[i->i]->type == P_END)
				i->is_open++;
			if (parse[i->i]->type == P_START)
				i->is_open--;
			if (i->is_open == i->depth && (parse[i->i]->type == PIPE
					|| parse[i->i]->type == OR || parse[i->i]->type == AND))
				break ;
			(i->i)--;
		}
		if (run_tree_content(node, parse, i))
			return (1);
	}
	return (base_tree(node, parse, i));
}
