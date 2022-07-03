/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_remove_if.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:49:21 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/21 17:50:53 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_list_remove_if(t_list **begin_list, void *data_ref
		, int (*cmp)(), void (*free_fct)(void *))
{
	t_list	*index;
	t_list	*prev;
	t_list	*del;

	index = *begin_list;
	prev = 0;
	while (index)
	{
		if ((*cmp)(index->content, data_ref) != 0)
		{
			if (prev)
				prev->next = index->next;
			else
				*begin_list = index->next;
			del = index;
			index = index->next;
			(*free_fct)(del->content);
			free(del);
		}
		else
		{
			prev = index;
			index = index->next;
		}
	}
}
