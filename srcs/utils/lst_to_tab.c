/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:05:19 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/07 00:03:47 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wildcard.h"
#include "utils.h"

char	**lst_to_tab_str(t_list **lst)
{
	char		**ret;
	t_list		*index;
	size_t		i;

	if (!lst)
		return (NULL);
	index = *lst;
	ret = ft_calloc(ft_lstsize(*lst) + 1, sizeof(char *));
	if (!ret)
		return (display_error("Error allcation\n", 0), NULL);
	i = 0;
	while (index)
	{
		ret[i] = ft_strdup((char *)index->content);
		if (!ret[i++])
		{
			free_tab(ret);
			return (display_error("Error allcation\n", 0), NULL);
		}
		index = index->next;
	}
	ret[i] = NULL;
	return (ret);
}
