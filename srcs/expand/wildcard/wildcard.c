/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 15:56:41 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/07 00:33:38 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "utils.h"
#include "libft.h"

static int	wildcards_end(t_list **lst_odd, t_list **lst_even,
				t_list **ret);

int	wildcards(t_wildcard	*mywc, t_list **ret)
{
	t_list	**lst_odd;
	t_list	**lst_even;
	int		r;

	*ret = ft_lstnew(mywc);
	if (!*ret)
		return (del_node_wc(mywc),
			display_error("Error allocation\n", 0), 1);
	lst_odd = ft_calloc(1, sizeof(t_list *));
	lst_even = ft_calloc(1, sizeof(t_list *));
	if (!lst_even || !lst_odd)
	{
		if (lst_odd)
			free(lst_odd);
		if (lst_even)
			free(lst_even);
		del_node_wc(mywc);
		return (free(ret), 1);
	}
	r = wildcards_end(lst_odd, lst_even, ret);
	free(lst_even);
	free(lst_odd);
	return (r);
}

static int	wildcards_end(t_list **lst_odd, t_list **lst_even,
				t_list **ret)
{
	int	t;

	t = 1;
	ft_lstadd_back(lst_odd, *ret);
	if (!rec_wildcards(lst_odd, lst_even))
	{
		if (lst_even && *lst_even)
			*ret = *lst_even;
		else if (lst_odd && *lst_odd)
			*ret = *lst_odd;
		else
			*ret = NULL;
		t = 0;
	}
	return (t);
}
