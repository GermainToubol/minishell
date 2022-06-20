/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:09:11 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/17 16:56:53 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include "libft.h"
#include "g_minishell.h"

/**
   Sort the given list in ascending order.

   @input: the list and a function comparing their content (positive if c1 > c2)
*/

static void	ft_lstsort_init(t_list **prev, t_list **min_prev, t_list **min,
				t_list *tmp);
static void	ft_lstsort_next(t_list *prev_min, t_list **min, t_list **lst);

void	ft_lstsort(t_list **lst, int (*f)(void *, void *))
{
	t_list	*prev;
	t_list	*tmp;
	t_list	*prev_min;
	t_list	*min;

	tmp = *lst;
	ft_lstsort_init(&prev, &prev_min, &min, tmp);
	if (tmp == NULL || tmp->next == NULL)
		return ;
	while (tmp != NULL)
	{
		if (f(min->content, tmp->content) > 0)
		{
			min = tmp;
			prev_min = prev;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	ft_lstsort_next(prev_min, &min, lst);
	ft_lstsort(&((*lst)->next), f);
}

static void	ft_lstsort_init(t_list **prev, t_list **min_prev, t_list **min,
				t_list *tmp)
{
	*prev = NULL;
	*min_prev = NULL;
	*min = tmp;
}

static void	ft_lstsort_next(t_list *prev_min, t_list **min, t_list **lst)
{
	if (prev_min != NULL)
	{
		prev_min->next = (*min)->next;
		(*min)->next = *lst;
		*lst = *min;
	}
}
