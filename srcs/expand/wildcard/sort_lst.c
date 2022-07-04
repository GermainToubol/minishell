/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 19:01:24 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/04 20:54:47 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

void	swap_data(void **data1, void **data2)
{
	void	*tmp;

	tmp = *data1;
	*data1 = *data2;
	*data2 = tmp;
}

static void	quicksort_void(void **tab, size_t len)
{
	size_t		i;
	size_t		pivot;

	if (len <= 1)
		return ;
	i = 0;
	pivot = 0;
	while (i < len)
	{
		if (ft_strcmp(tab[i], tab[len - 1]) < 0)
		{
			swap(tab + i, tab + pivot++);
		}
		i++;
	}
	swap_data(tab + pivot, tab + len - 1);
	quicksort(tab, pivot++);
	quicksort(&tab[pivot], len - pivot);
}

void	index_list(t_list **lst)
{
	size_t	size;
	t_list	*index;
	void	**tab;

	if (!lst || !*lst)
		return ;
	size = ft_lstsize(*lst);
	tab = ft_calloc(size, sizeof(void *));
	if (!tab)
		return ;
	index = *lst;
	size = 0;
	while (index)
	{
		tab[size++] = index->content;
		index = index->next;
	}
	quicksort_void(tab, size);
	free(tab);
}