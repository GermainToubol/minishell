/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rec_wc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 02:22:00 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/20 16:37:36 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "libft.h"
#include "utils.h"

static int	get_match_indir_content(t_wildcard *mywc,
					t_list **new_lst, struct dirent	*dir)
{
	t_wildcard		*new;
	t_list			*node;

	new = prefix_suffix(mywc, dir->d_name);
	if (new)
	{
		ft_printf("dir: %s\n", dir->d_name);
		node = ft_lstnew(new);
		if (!node)
			return (display_error("Error allocation\n", 0) ,-1);
		ft_lstadd_back(new_lst, ft_lstnew(new));
	}
	return (0);
}

static int	get_match_indir(t_list *old_lst, t_list **new_lst)
{
	struct dirent	*dir;
	DIR				*d;
	t_wildcard		*mywc;


	mywc = (t_wildcard *)old_lst->content;
	d = opendir(mywc->dir_path);
	if (!d)
		return (1);
	while (1)
	{
		dir = readdir(d);
		if (!dir)
			break ;
		if (get_match_indir_content(mywc, new_lst, dir) == -1)
			return (closedir(d), -1);
	}
	closedir(d);
	return (0);
}

static int	iter_lst(t_list **lst, t_list **new)
{
	t_list	*index;

	if (!lst || !*lst)
		return (1);
	index = *lst;
	while (index)
	{
		if (get_match_indir(index, new) == -1)
			return (1);
		index = index->next;
	}
	ft_lstclear(lst, del_node);
	ft_printf("\n");
	ft_lstiter(*new, print_lst2);
	ft_printf("\n");
	return (0);
}

int	rec_wildcards(t_list **lst, t_list **new_lst)
{
	t_wildcard	*wc;

	if (!lst || !*lst)
		return (1);
	wc = (t_wildcard *)(*lst)->content;
	if (wc->suffix == NULL)
		return (0);
	if (iter_lst(lst, new_lst))
		return (1);
	return (rec_wildcards(new_lst, lst));
}
