/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 19:01:24 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/06 23:57:55 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

static void	swap_data(void **a, void **b);
static void	quicksort_lst(t_list **lst, size_t len);

void	sort_list(t_list **lst)
{
	size_t	size;

	if (!lst || !*lst)
		return ;
	size = ft_lstsize(*lst);
	quicksort_lst(lst, size);
}

static void	quicksort_lst(t_list **lst, size_t len)
{
	size_t		i;
	size_t		pivot;
	t_list		*new_start;

	if (len <= 1)
		return ;
	i = 0;
	pivot = 0;
	while (i < len)
	{
		if (ft_strcmp(ft_list_at(*lst, i)->content,
				ft_list_at(*lst, len - 1)->content) < 0)
		{
			swap_data(&(ft_list_at(*lst, i)->content),
				&(ft_list_at(*lst, pivot)->content));
			pivot++;
		}
		i++;
	}
	swap_data(&(ft_list_at(*lst, pivot)->content),
		&(ft_list_at(*lst, len - 1)->content));
	quicksort_lst(lst, pivot++);
	new_start = ft_list_at(*lst, pivot);
	quicksort_lst(&new_start, len - pivot);
}

static void	swap_data(void **a, void **b)
{
	void	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}