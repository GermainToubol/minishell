/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_str_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 22:15:47 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/04 22:17:49 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	del_node_str(void *data)
{
	char 	*tmp;

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

void	print_lst(void *data)
{
	ft_printf("data: %s\n", (char *)data);
}
