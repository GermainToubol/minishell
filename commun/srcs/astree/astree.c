/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:03:51 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/18 14:09:59 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astree.h"
#include "utils.h"

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
		return (free(i), 1);
	free(i);
	astree_apply_prefix(*root);
	return (0);
}
