/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_str_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 22:15:47 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/07 22:12:46 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include <stdlib.h>

int	cat_lst(t_list **dest, t_list **src)
{
	t_list	*index;
	t_list	*new;
	char	*tmp;

	if (!dest || !src)
		return (1);
	index = *src;
	while (index)
	{
		tmp = ft_strdup((char *)index->content);
		if (!tmp)
			return (error_alloc(), 1);
		new = ft_lstnew(tmp);
		if (!new)
			return (free(tmp), error_alloc(), 1);
		ft_lstadd_back(dest, new);
		index = index->next;
	}
	return (0);
}

void	del_node_str(void *data)
{
	char	*tmp;

	if (!data)
		return ;
	tmp = (char *)data;
	free(tmp);
}

void	free_lst_str(t_list **lst)
{
	if (!lst)
		return ;
	if (!*lst)
		return (free(lst));
	ft_lstclear(lst, del_node_str);
	free(lst);
}

void	print_node_str(void *data)
{
	ft_printf("data: %s\n", (char *)data);
}
