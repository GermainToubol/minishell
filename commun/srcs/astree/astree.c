/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:03:51 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/19 15:26:03 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astree.h"
#include "utils.h"

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

static int	create_astree_content(t_astree **root, t_parse **parse)
{
	t_int_help	*i;

	i = fill_t_int(parse, 0, 0);
	if (!i)
		return (1);
	*root = create_node(parse[i->i]);
	if (!*root)
		return (free(i), 1);
	i->i--;
	if (run_tree(*root, parse, i))
	{
		astree_apply_suffix(*root, free_tree);
		return (free(i), 1);
	}
	free(i);
	return (0);
}

int	create_astree(t_parse **parse, t_astree **root)
{
	if (!parse || !root)
		return (1);
	if (parse[1] == NULL)
	{
		*root = create_node(parse[0]);
		if (!root)
			return (1);
	}
	else
		if (create_astree_content(root, parse))
			return (1);
	return (0);
}
