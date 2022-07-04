/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:05:19 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/04 22:37:40 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wildcard.h"
#include "utils.h"

char	**lst_to_tab_wc(t_list **lst)
{
	char		**ret;
	t_list		*index;
	t_wildcard	*tmp;
	size_t		i;

	if (!lst || !*lst)
		return (NULL);
	index = *lst;
	ret = ft_calloc(ft_lstsize(*lst) + 1, sizeof(char *));
	if (!ret)
		return (display_error("Error allcation\n", 0), NULL);
	i = 0;
	while (index)
	{
		tmp = (t_wildcard *)index->content;
		ret[i] = ft_strdup(tmp->prefix);
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

char	**lst_to_tab_str(t_list **lst)
{
	char		**ret;
	t_list		*index;
	size_t		i;

	if (!lst || !*lst)
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