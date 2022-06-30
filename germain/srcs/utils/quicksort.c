/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_sort_custom.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:42:32 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/22 00:16:17 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wildcard.h"
#include "utils.h"

void	swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	quicksort(char **tab, size_t len)
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
	swap(tab + pivot, tab + len - 1);
	quicksort(tab, pivot++);
	quicksort(&tab[pivot], len - pivot);
}
