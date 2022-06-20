/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rec_wc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 02:22:00 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/20 19:35:16 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "libft.h"
#include "utils.h"

static int	get_match_indir_content(t_wildcard *mywc,
					t_list **new_lst, char *dir_name)
{
	t_wildcard		*new;
	t_list			*node;

	if (dir_name[0] == '.')
		return (0);
	new = prefix_suffix(mywc, dir_name);
	if (new)
	{
		node = ft_lstnew(new);
		if (!node)
			return (display_error("Error allocation\n", 0), -1);
		ft_lstadd_back(new_lst, node);
	}
	return (0);
}

static int	get_dir_match(t_wildcard *mywc, t_list **new_lst)
{
	t_wildcard	*new;
	t_list		*node;

	if (mywc->suffix[0] == '\0')
	{
		new = cpy_wc(mywc);
		if (!new)
			return (-1);
		node = ft_lstnew(new);
		if (!node)
			return (display_error("Error allocation\n", 0), -1);
		ft_lstadd_back(new_lst, node);
		return (0);
	}
	return (1);
}

static int	get_match_indir(t_list *old_lst, t_list **new_lst)
{
	struct dirent	*dir;
	DIR				*d;
	t_wildcard		*mywc;
	int				t;

	mywc = (t_wildcard *)old_lst->content;
	d = opendir(mywc->dir_path);
	if (!d)
		return (1);
	while (1)
	{
		t = get_dir_match(mywc, new_lst);
		if (t == -1)
			return (-1);
		if (t == 0)
			return (closedir(d), 0);
		dir = readdir(d);
		if (!dir)
			break ;
		if (get_match_indir_content(mywc, new_lst, dir->d_name) == -1)
			return (closedir(d), -1);
	}
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
			if (get_match_indir_content(wc, new, wc->found) == -1)
				return (1);
		index = index->next;
	}
	ft_lstclear(lst, del_node);
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
