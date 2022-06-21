/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:42:32 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/21 17:48:43 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

void	ft_lst_sort(t_list **begin_list, int (*cmp)())
{
	t_list	*index;
	void	*tmp;

	index = *begin_list;
	if (!index)
		return ;
	while (index->next)
	{
		if ((*cmp)(index->content, (index->next)->content) > 0)
		{
			tmp = index->content;
			index->content = (index->next)->content;
			(index->next)->content = tmp;
			index = *begin_list;
		}
		else
			index = index->next;
	}
}
