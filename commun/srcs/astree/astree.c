/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:03:51 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/17 23:03:50 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astree.h"
#include "utils.h"

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

int	base_tree(t_astree *node, t_parse **parse, t_int_help *i)
{
	if (i->is_done)
	{
		if (parse[i->i] && (parse[i->i]->type == PIPE
			|| parse[i->i]->type == OR || parse[i->i]->type == AND))
				(i->i)++;
		if (parse[i->i] && parse[i->i]->type == CMD)
		{
			node->right = create_node(parse[i->i]);
			if (!node->right)
				return (1);
			(i->i)++;
		}
	}
	return (0);
}

int	run_tree(t_astree *node, t_parse **parse, t_int_help *i)
{
	if (!i->is_done)
	{
		while (i->i > i->min && (parse[i->i]->type != PIPE
				&& parse[i->i]->type != OR && parse[i->i]->type != AND))
					(i->i)--;
		if (i->i == i->min && parse[i->i]->type == CMD)
		{
			node->left = create_node(parse[i->i]);
			if (!node->left)
				return (1);
			i->is_done = 1;
			(i->i)++;
		}
		else
		{
			node->left = create_node(parse[i->i]);
			if (!node->left)
				return (1);
			(i->i)--;
			if (run_tree(node->left, parse, i))
				return (1);
		}
	}
	return (base_tree(node, parse, i));
}

t_int_help	*fill_t_int(t_parse **parse, int depth, int start)
{
	t_int_help	*i;

	i = ft_calloc(1, sizeof(t_int_help));
	if (!i)
		return (display_error("Error allocation\n", 0), NULL);
	i->i = start;
	i->min = start;
	i->is_open = depth;
	i->is_done = 0;
	while (parse[i->i] && i->is_open >= depth)
	{
		if (parse[i->i]->type == P_END)
			i->is_open--;
		if (parse[i->i]->type == P_START)
			i->is_open++;
		i->i++;
	}
	i->max = i->i;
	i->i--;
	while (i->i > i->min)
	{
		if (parse[i->i]->type == P_END)
			i->is_open--;
		if (parse[i->i]->type == P_START)
			i->is_open++;
		if (parse[i->i]->type == PIPE || parse[i->i]->type == OR
			|| parse[i->i]->type == AND)
			break ;
		i->i--;
	}
	return (i);
}

int	create_astree(t_astree **root, t_parse **parse)
{
	t_int_help	*i;

	i = fill_t_int(parse, 0, 0);
	if (!i)
		return (1);
	*root = create_node(parse[i->i]);
	if (!*root)
		return (1);
	i->i--;
	if (run_tree(*root, parse, i))
		return (1);
	astree_apply_prefix(*root);
	return (0);
}
