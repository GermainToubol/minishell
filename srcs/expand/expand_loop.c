/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 03:47:46 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/04 21:19:29 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "expand.h"
#include "libft.h"
#include "utils.h"

static int	transfer_lst(t_list **dest, t_list **src)
{
	t_list *index;
	t_list *new;

	if (!dest || !src)
		return (1);
	index = *src;
	while (index)
	{
		ft_lstadd_back(dest, index);
		index = index->next;
	}
	*src = NULL;
	return (0);
}

int	expand_loop(char *cmd, t_list **lst, t_list **lst_tmp)
{
	if (!cmd)
		return (transfer_lst(lst_tmp, lst));
	return (0);
}