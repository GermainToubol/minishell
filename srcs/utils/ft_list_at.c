/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_at.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 13:59:41 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/05 03:11:10 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_list_at(t_list *begin_list, unsigned int nbr)
{
	t_list			*index;
	unsigned int	i;

	i = 0;
	index = begin_list;
	while (index && i < nbr)
	{
		index = index->next;
		i++;
	}
	if (i != nbr)
		return (0);
	return (index);
}
