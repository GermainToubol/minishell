/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:01:02 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/22 15:08:57 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "utils.h"

int	check_found(t_wildcard *mywc, t_list **new_lst, char *dir_name)
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
		{
			del_node(new);
			return (display_error("Error allocation\n", 0), -1);
		}
		ft_lstadd_back(new_lst, node);
	}
	return (0);
}

int	get_dir_match(t_wildcard *mywc, t_list **new_lst)
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
		{
			del_node(new);
			return (display_error("Error allocation\n", 0), -1);
		}
		ft_lstadd_back(new_lst, node);
		return (0);
	}
	return (1);
}

char	*get_dir_name(t_wildcard *wc)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	i = last_char(wc->prefix, '/');
	tmp = ft_substr(wc->prefix, 0, i + 1);
	if (!tmp)
		return (display_error("Error allocation\n", 0), NULL);
	if (wc->dir_path[0] == '\0')
		return (tmp);
	else
	{
		tmp2 = ft_join3(wc->dir_path, "/", tmp);
		free(tmp);
		if (!tmp2)
			return (display_error("Error allocation\n", 0), NULL);
		return (tmp2);
	}
}
