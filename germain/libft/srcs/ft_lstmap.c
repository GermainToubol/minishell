/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 10:21:28 by gtoubol           #+#    #+#             */
/*   Updated: 2022/05/09 11:02:40 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_elem;
	t_list	*new_lst;
	t_list	*tmp;

	new_lst = NULL;
	tmp = NULL;
	while (lst != NULL)
	{
		new_elem = ft_lstnew((*f)(lst->content));
		if (new_elem == NULL)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		if (tmp)
			tmp->next = new_elem;
		else
			new_lst = new_elem;
		tmp = new_elem;
		lst = lst->next;
	}
	return (new_lst);
}
