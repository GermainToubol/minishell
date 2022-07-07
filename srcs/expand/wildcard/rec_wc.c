/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rec_wc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 02:22:00 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/07 14:13:07 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "libft.h"
#include "utils.h"

static int	get_match_indir_loop(t_list **new_lst, t_wildcard *mywc, DIR *d)
{
	int				t;
	struct dirent	*dir;
	char			*dir_name;

	while (42)
	{
		t = get_dir_match(mywc, new_lst);
		if (t <= 0)
			return (t);
		dir = readdir(d);
		if (!dir)
			break ;
		dir_name = add_backslash(dir->d_name);
		if (check_found(mywc, new_lst, dir_name) == -1)
			return (free(dir_name), -1);
		free(dir_name);
	}
	return (0);
}

static int	get_match_indir(t_list *old_lst, t_list **new_lst)
{
	DIR				*d;
	t_wildcard		*mywc;
	char			*tmp;

	mywc = (t_wildcard *)old_lst->content;
	tmp = get_dir_name(mywc);
	if (!tmp)
		return (-1);
	d = opendir(tmp);
	free(tmp);
	if (!d)
		return (1);
	if (get_match_indir_loop(new_lst, mywc, d) == -1)
		return (closedir(d), -1);
	closedir(d);
	return (0);
}

static int	iter_lst(t_list **lst, t_list **new)
{
	t_list		*index;
	t_wildcard	*wc;

	if (!lst || !*lst)
		return (1);
	index = *lst;
	while (index)
	{
		wc = (t_wildcard *)index->content;
		if (wc->found == NULL)
		{
			if (get_match_indir(index, new) == -1)
				return (1);
		}
		else
			if (check_found(wc, new, wc->found) == -1)
				return (1);
		index = index->next;
	}
	ft_lstclear(lst, del_node_wc);
	return (0);
}

int	rec_wildcards(t_list **lst, t_list **new_lst)
{
	t_wildcard	*wc;

	if (!lst)
		return (1);
	if (!*lst)
		return (0);
	wc = (t_wildcard *)(*lst)->content;
	if (wc->suffix == NULL)
		return (0);
	if (iter_lst(lst, new_lst))
	{
		ft_lstclear(lst, del_node_wc);
		ft_lstclear(new_lst, del_node_wc);
		return (1);
	}
	return (rec_wildcards(new_lst, lst));
}
