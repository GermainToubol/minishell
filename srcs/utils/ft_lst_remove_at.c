/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_remove_at.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:49:21 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/06 23:42:23 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	swap_index(t_list **prev, t_list **index,
				t_list **del, t_list **begin_list);

void	ft_list_remove_at(t_list **begin_list, unsigned int nb,
			void (*free_fct)(void *))
{
	t_list			*index;
	t_list			*prev;
	t_list			*del;
	unsigned int	i;

	index = *begin_list;
	prev = 0;
	i = 0;
	while (index)
	{
		if (i++ == nb)
		{
			swap_index(&prev, &index, &del, begin_list);
			(*free_fct)(del->content);
			free(del);
			break ;
		}
		else
		{
			prev = index;
			index = index->next;
		}
	}
}

static void	swap_index(t_list **prev, t_list **index,
				t_list **del, t_list **begin_list)
{
	if (*prev)
		(*prev)->next = (*index)->next;
	else
		*begin_list = (*index)->next;
	(*del) = (*index);
	(*index) = (*index)->next;
}
