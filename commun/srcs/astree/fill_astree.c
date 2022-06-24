/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_astree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:09:36 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/25 01:38:13 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astree.h"
#include "utils.h"

int	start_p(t_parse **parse, t_int_help *i)
{
	int	index;
	int	is_open;

	is_open = 1;
	index = i->i;
	while (is_open && --index >= i->min)
	{
		if (parse[index]->type == P_END)
			is_open++;
		if (parse[index]->type == P_START)
			is_open--;
	}
	return (index);
}

int	get_next_left(t_parse **parse, t_int_help *i, int type)
{
	int	index;
	int	is_open;

	index = i->i;
	is_open = i->depth;
	while (--index >= i->min)
	{
		if (parse[index]->type == P_END)
				is_open++;
		if (parse[index]->type == P_START)
				is_open--;
		if (type == 0 && is_open == i->depth
			&& (parse[index]->type == OR || parse[index]->type == AND))
			return (index);
		if (type == 1 && is_open == i->depth && parse[index]->type == PIPE)
			return (index);
		if (type == 2 && is_open == i->depth && parse[index]->type == CMD)
			return (index);
		if (type == 3 && parse[index]->type == P_END)
			return (index);
	}
	if (type < 3)
		return (get_next_left(parse, i, type + 1));
	return (-1);
}

int	get_next_right(t_parse **parse, t_int_help *i, int type)
{
	int	index;
	int	is_open;

	index = i->max;
	is_open = i->depth;
	while (--index >= i->min)
	{
		if (parse[index]->type == P_START)
				is_open++;
		if (parse[index]->type == P_END)
				is_open--;
		if (type == 0 && is_open == i->depth
			&& (parse[index]->type == PIPE))
			return (index);
	}
	return (i->i + 1);
}

t_int_help	*new_right(t_parse **parse, t_int_help *i, int min)
{
	t_int_help	*new;

	new = ft_calloc(1, sizeof(t_int_help));
	if (!new)
		return (display_error("Error allocation", 0), NULL);
	new->min = min + 1;
	new->depth = i->depth;
	while (new->depth >= i->depth && ++min < i->max)
	{
		if (parse[min]->type == P_START)
			new->depth++;
		if (parse[min]->type == P_END)
			new->depth--;
		if (new->depth == i->depth && (parse[min]->type == OR
				|| parse[min]->type == AND))
			break ;
	}
	new->depth = i->depth;
	new->max = min;
	new->i = i->i;
	new->is_open = 0;
	return (new);
}
