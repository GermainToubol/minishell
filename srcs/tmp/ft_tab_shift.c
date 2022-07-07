/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_shift.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 12:21:22 by gtoubol           #+#    #+#             */
/*   Updated: 2022/07/07 12:54:51 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

/**
   Shif a {VAR1, VAR2, VAR3, ..., NULL} array from n index to the left.

   Poped values are freed and the array is NULL terminated.
*/

static size_t	ft_splitsize(char **tab)
{
	size_t	i;

	i = 0;
	while (tab != NULL && tab[i] != NULL)
		i++;
	return (i);
}

void	ft_tab_shift(char **tab, size_t n)
{
	size_t	i;
	size_t	j;

	if (n == 0)
		return ;
	i = 0;
	j = ft_splitsize(tab);
	while (i < j)
	{
		if (i < n)
			free(tab[i]);
		if (n + i < j)
			tab[i] = tab[n + i];
		else
			tab[i] = NULL;
		i++;
	}
}
