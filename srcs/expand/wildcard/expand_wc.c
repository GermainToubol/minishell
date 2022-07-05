/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 03:33:06 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/05 05:10:44 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "expand.h"
#include "libft.h"
#include "utils.h"

static int	cpy_lst_wc_to_str(t_list **dest, t_list **src)
{
	t_list 		*index;
	t_list 		*new;
	t_wildcard	*wc;
	char		*tmp;

	if (!dest || !src)
		return (1);
	index = *src;
	while (index)
	{
		wc = (t_wildcard *)index->content;
		tmp = ft_strdup(wc->prefix);
		if (!tmp)
			return (display_error("Error allocation\n", 0), 1);
		new = ft_lstnew(tmp);
		if (!new)
		{
			free(tmp);
			return (display_error("Error allocation\n", 0), 1);
		}
		ft_lstadd_back(dest, new);
		index = index->next;
	}
	return (0);
}

static int	get_prefix_path(t_list *lst_tmp, char **path, char **prefix)
{
	char	*line;
	int		delimiter;
	char	cwd_dir[DIR_BUFFER];

	if (lst_tmp)
	{
		line = (char *)lst_tmp->content;
		delimiter = last_char(line, '/');
		if (delimiter < 0 && strjoin_custom(prefix, ft_strdup(line)))
			return (1);
		else
		{
			if (strjoin_custom(path, ft_substr(line, 0, delimiter + 1)))
				return (1);
			if (strjoin_custom(prefix, ft_substr(line, delimiter + 1,
				ft_strlen(line) - delimiter - 1)))
				return (free(*path), 1);
		}

	}
	else if (strjoin_custom(prefix, ft_strdup("")))
		return (1);
	else if (strjoin_custom(path, ft_strdup(getcwd(cwd_dir, DIR_BUFFER))))
		return (free(prefix), 1);
	return (0);
}

t_wildcard	*get_wc_line(const char *cmd, t_list *lst_tmp, size_t *next)
{
	char	*str[3];

	*next = 1;
	str[0] = NULL;
	str[1] = NULL;
	if (get_prefix_path(lst_tmp, &str[0], &str[1]))
		return (NULL);
	*next = to_next_index(&cmd[*next]);
	(*next)++;
	str[2] = NULL;
	if (strjoin_custom(&str[2], ft_substr(cmd, 0, *next)))
		return (free(str[0]), free(str[1]), NULL);
	return (init_wc_2(str[0], str[1], str[2]));
}

static int parent_wc(t_list **lst, t_list **lst_tmp, int i_parent)
{
	t_list	*index;
	t_list	*parent;
	char	*tmp;

	index = *lst;
	parent = ft_list_at(*lst_tmp, i_parent);
	while (index)
	{
		tmp = NULL;
		if (strjoin_custom(&tmp, ft_strdup((char *)parent->content)))
			return (1);
		if (strjoin_custom(&tmp, (char *)index->content))
			return (free(tmp), 1);
		index->content = (void *)tmp;
		index = index->next;
	}
	ft_list_remove_at(lst_tmp, i_parent, del_node_str);
	cat_lst(lst_tmp, lst);
	return (0);
}

int	wc_found(t_list **lst_tmp, t_list **wc_lst, int parent)
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
	if (parent == -1 && cat_lst(lst_tmp, lst))
		return (free_lst_str(lst), 1);
	else if (parent >= 0)
	{
		if (parent_wc(lst, lst_tmp, parent))
			return (1);
	}
	free_lst_str(lst);
	return (0);
}

int	expand_wc_content(t_wildcard *wc, t_list **lst_tmp, int	parent)
{
	t_list		**wc_lst;

	wc_lst = ft_calloc(1, sizeof(t_list *));
	if (!wc_lst)
		return (display_error("Error allcation\n", 0), -1);
	if (wildcards_wc(wc, wc_lst))
	{
		ft_lstclear(wc_lst, del_node_wc);
		return (free(wc_lst), -1);
	}
	if (*wc_lst)
	{
		if (wc_found(lst_tmp, wc_lst, parent))
			return (ft_lstclear(wc_lst, del_node_wc), free(wc_lst), -1);
		ft_lstclear(wc_lst, del_node_wc);
		free(wc_lst);
		return (1);
	}
	free(wc_lst);
	return (0);
}

int expand_wc(const char *cmd, t_list **lst_tmp, size_t *next)
{
	t_wildcard	*tmp;
	t_list		*index;
	size_t		i;
	int			r;

	if (!lst_tmp)
		return (1);
	i = 0;
	index = *lst_tmp;
	if (!index)
	{
		tmp = get_wc_line(cmd, index, next);
		if (!tmp)
			return (1);
		r = expand_wc_content(tmp, lst_tmp, -1);
		if (r == -1)
			return (1);
		else if (r == 0 && do_basic_lst(cmd, &index, next))
			return (1);
	}
	while (index)
	{
		*next = 0;
		tmp = get_wc_line(cmd, index, next);
		if (!tmp)
			return (1);
		r = expand_wc_content(tmp, lst_tmp, i);
		if (r == -1)
			return (1);
		else if (r == 0 && do_basic_lst(cmd, &index, next))
			return (1);
		index = index->next;
		i++;
	}
	return (0);
}
