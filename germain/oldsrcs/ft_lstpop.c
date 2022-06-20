/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:58:04 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/09 13:02:39 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include "libft.h"
#include "g_minishell.h"

void	ft_lstpop(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (*lst == NULL)
		return ;
	tmp = (*lst)->next;
	ft_lstdelone(*lst, del);
	*lst = tmp;
}
