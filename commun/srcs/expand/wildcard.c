/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 15:56:41 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/22 14:17:03 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "parser.h"
#include "utils.h"
#include <unistd.h>

static t_list	*wildcards_content(t_wildcard *mywc, t_list *ret)
{
	t_list		**lst_odd;
	t_list		**lst_even;

	lst_odd = ft_calloc(1, sizeof(t_list *));
	lst_even = ft_calloc(1, sizeof(t_list *));
	if (!lst_even || !lst_odd)
	{
		if (lst_odd)
			free(lst_odd);
		if (lst_even)
			free(lst_even);
		del_node(mywc);
		return (free(ret), NULL);
	}
	ft_lstadd_back(lst_odd, ret);
	ret = NULL;
	if (!rec_wildcards(lst_odd, lst_even))
	{
		if (!lst_even || !*lst_even)
			ret = *lst_odd;
		else
			ret = *lst_even;
	}
	free(lst_even);
	return (free(lst_odd), ret);
}

int	wildcards(char *line, t_list **ret)
{
	t_wildcard	*mywc;

	if (ft_strchr(line, '*') == NULL)
		return (0);
	mywc = init_wc(line);
	if (!mywc)
		return (1);
	if (update_wildcard(mywc, line))
		return (del_node(mywc), 1);
	*ret = ft_lstnew(mywc);
	if (!*ret)
	{
		del_node(mywc);
		return (display_error("Error allocation\n", 0), 1);
	}
	*ret = wildcards_content(mywc, *ret);
	if (!*ret)
		return (1);
	return (0);
}
