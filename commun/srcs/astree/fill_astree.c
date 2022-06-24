/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_astree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:09:36 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/24 22:53:22 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astree.h"
#include "utils.h"

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

int	get_next_left(t_parse **parse, t_int_help *i, int type)
{
	int	index;
	int	is_open;

	index = i->i;
	is_open = i->is_open;
	while (--index >= i->min)
	{
		if (parse[index]->type == P_END)
				is_open++;
		if (parse[index]->type == P_START)
				is_open--;
		if (type == 0 && is_open == i->depth
			&& (parse[index]->type == OR || parse[index]->type == AND))
			return (index) ;
		if (type == 1 && is_open == i->depth
			&& (parse[index]->type == PIPE))
			return (index) ;
		if (type == 2 && is_open == i->depth
			&& (parse[index]->type == CMD))
			return (index) ;
		if (type == 3 && parse[index]->type == P_END)
			return (index) ;
	}
	if (type < 3)
		return (get_next_left(parse, i, type + 1));
	return (-1);
}

int	get_next_right(t_parse **parse, t_int_help *i, int type)
{
	int	index;
	int	is_open;

	index = i->i;
	is_open = i->is_open;
	while (++index < i->max)
	{
		if (parse[index]->type == P_START)
				is_open++;
		if (parse[index]->type == P_END)
				is_open--;
		if (type == 0 && is_open == i->depth
			&& (parse[index]->type == PIPE))
			return (index) ;
		if (type == 1 && is_open == i->depth
			&& (parse[index]->type == CMD))
			return (index) ;
		if (type == 2 && parse[index]->type == P_START)
			return (index) ;
	}
	if (type < 2)
		return (get_next_right(parse, i, type + 1));
	return (-1);
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
	if (node->cmd->type == PIPE)
		i->i = get_next_right(parse, i, 1);
	else
		i->i = get_next_right(parse, i, 0);
	if (i->i == -1)
		return (0);
	if (parse[i->i]->type == P_START)
	{
		if (p_after(node, parse, i))
			return (1);
	}
	else
	{
		node->right = create_node(parse[i->i], i->depth);
		if (!node->right)
			return (1);
		if (parse[i->i]->type != CMD && run_tree(node->right, parse, i))
			return (1);
	}
	return (0);
}

int	run_tree(t_astree *node, t_parse **parse, t_int_help *i)
{
	if (run_tree_right(node, parse, i))
		return (1);
	if (run_tree_left(node, parse, i))
		return (1);
	return (0);
}
