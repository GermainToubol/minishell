/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:05:19 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/21 18:07:18 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

char	**lst_to_tab(t_list **lst)
{
	char	**ret;
	t_list	*index;
	char	*tmp;
	size_t	i;

	if (!lst || !*lst)
		return (NULL);
	index = *lst;
	ret = ft_calloc(ft_lstsize(*lst) + 1, sizeof(char *));
	if (!ret)
		return (display_error("Error allcation\n", 0), NULL);
	i = 0;
	while (index)
	{
		tmp = (char *)index->content;
		ret[i] = ft_strdup(tmp);
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
