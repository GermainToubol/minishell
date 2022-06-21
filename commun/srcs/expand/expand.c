/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:46:41 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/21 18:15:23 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "expand.h"
#include "libft.h"
#include "utils.h"

static int	do_wildcard(t_list **wc_lst, t_list **new_lst)
{
	t_list		*index;
	t_list		*new;
	t_wildcard	*wc;
	char		*tmp;

	if (!wc_lst || !*wc_lst)
		return (1);
	index = *wc_lst;
	while (index)
	{
		wc = (t_wildcard *)index->content;
		tmp = ft_strdup(wc->prefix);
		if (!tmp)
			return (display_error("Error allcation\n", 0), -1);
		new = ft_lstnew(tmp);
		if (!new)
		{
			free(tmp);
			return (display_error("Error allcation\n", 0), -1);
		}
		ft_lstadd_back(new_lst, new);
		index = index->next;
	}
	return (0);
}

static int	do_basic(char *cmd, t_list **new_lst)
{
	char	*tmp;
	t_list	*new;

	tmp = ft_strdup(cmd);
	if (!tmp)
		return (display_error("Error allcation\n", 0), 1);
	new = ft_lstnew(tmp);
	if (!new)
	{
		free(tmp);
		return (display_error("Error allcation\n", 0), 1);
	}
	ft_lstadd_back(new_lst, new);
	return (0);
}

static int	do_expand_loop(char **cmd, t_list **new_lst)
{
	size_t	i;
	t_list	*wc_lst;

	i = 0;
	while (cmd[i])
	{
		wc_lst = wildcards(cmd[i]);
		if (wc_lst)
		{
			ft_lst_sort(&wc_lst, ft_strcmp);
			if (do_wildcard(&wc_lst, new_lst) == -1)
				return (ft_lstclear(&wc_lst, del_node), 1);
			ft_lstclear(&wc_lst, del_node);
		}
		else
			if (do_basic(cmd[i], new_lst))
				return (1);
		i++;
	}
	return (0);
}

char	**do_expand(char **cmd)
{
	t_list	**new_lst;
	char	**new_cmd;

	new_lst = ft_calloc(1, sizeof(t_list *));
	if (!new_lst)
	{
		free_tab(cmd);
		return (display_error("Error allcation\n", 0), NULL);
	}
	if (do_expand_loop(cmd, new_lst))
	{
		free_tab(cmd);
		ft_lstclear(new_lst, free_ptr);
		return (free(new_lst), NULL);
	}
	free_tab(cmd);
	new_cmd = lst_to_tab(new_lst);
	ft_lstclear(new_lst, free_ptr);
	free(new_lst);
	return (new_cmd);
}
