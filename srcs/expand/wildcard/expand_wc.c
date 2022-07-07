/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 03:33:06 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/07 18:34:40 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "expand.h"
#include "libft.h"
#include "utils.h"

static int	expand_wc_content(t_wildcard *wc, t_list **lst_tmp);
static int	wc_found(t_list **lst_tmp, t_list **wc_lst);

int	expand_wc(char *cmd, t_expand *expand)
{
	t_wildcard	*wc;

	wc = get_wc_line(cmd);
	if (!wc)
		return (1);
	if (expand_wc_content(wc, expand->tmp))
		return (1);
	return (0);
}

static int	expand_wc_content(t_wildcard *wc, t_list **lst_tmp)
{
	t_list		**wc_lst;

	wc_lst = ft_calloc(1, sizeof(t_list *));
	if (!wc_lst)
		return (del_node_wc(wc), display_error("Error allocation\n", 0), 1);
	if (wildcards(wc, wc_lst))
	{
		return (free(wc_lst), 1);
	}
	if (*wc_lst)
	{
		if (wc_found(lst_tmp, wc_lst))
			return (ft_lstclear(wc_lst, del_node_wc), free(wc_lst), 1);
		ft_lstclear(wc_lst, del_node_wc);
		free(wc_lst);
		return (0);
	}
	free(wc_lst);
	return (0);
}

static int	wc_found(t_list **lst_tmp, t_list **wc_lst)
{
	t_list	**lst;

	lst = ft_calloc(1, sizeof(t_list *));
	if (!lst)
		return (display_error("Error allocation\n", 0), 1);
	*lst = NULL;
	if (cpy_lst_wc_to_str(lst, wc_lst))
	{
		free_lst_str(lst);
		return (1);
	}
	sort_list(lst);
	if (cat_lst(lst_tmp, lst))
		return (free_lst_str(lst), 1);
	free_lst_str(lst);
	return (0);
}
