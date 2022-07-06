/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 03:33:06 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/06 20:49:33 by fmauguin         ###   ########.fr       */
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

size_t	to_next_wc(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '*' && (i == 0 || s[i - 1] != '\\'))
			return (i + 1);
		i++;
	}
	return (0);
}

static int	get_prefix_path(char **path, char **prefix, char *to_add)
{
	if (to_add[0] == '/' && strjoin_custom(path, ft_strdup(("/"))))
		return (1);
	if (strjoin_custom(prefix, to_add))
			return (free(*path), 1);
	// if (clean_backslash(prefix))
	// 	return (free(*prefix), free(*path), 1);
	return (0);
}

t_wildcard	*get_wc_line(const char *cmd)
{
	char	*str[4];
	size_t	i;

	str[0] = NULL;
	str[1] = NULL;
	i = to_next_wc(cmd);
	if (i == 0)
		return (NULL);
	i--;
	str[3] = ft_substr(cmd, 0, i);
	if (!str[3])
		return (display_error("Error allocation\n", 0), NULL);
	cmd = &cmd[i];
	if (get_prefix_path(&str[0], &str[1], str[3]))
		return (free(str[3]), NULL);
	str[2] = NULL;
	if (strjoin_custom(&str[2], ft_strdup(cmd)))
		return (free(str[0]), free(str[1]), NULL);
	return (init_wc_2(str[0], str[1], str[2]));
}

int	wc_found(t_list **lst_tmp, t_list **wc_lst)
{
	t_list	**lst;

	lst = ft_calloc(1, sizeof(t_list *));
	if (!lst)
		return (display_error("Error allocation\n", 0), 1);
	*lst = NULL;
	ft_lstiter(*wc_lst, print_lst2);
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

int	expand_wc_content(t_wildcard *wc, t_list **lst_tmp)
{
	t_list		**wc_lst;

	wc_lst = ft_calloc(1, sizeof(t_list *));
	if (!wc_lst)
		return (display_error("Error allcation\n", 0), 1);
	if (wildcards_wc(wc, wc_lst))
	{
		ft_lstclear(wc_lst, del_node_wc);
		return (free(wc_lst), -1);
	}
	if (*wc_lst)
	{
		ft_printf("\nMATCH\n");
		if (wc_found(lst_tmp, wc_lst))
			return (ft_lstclear(wc_lst, del_node_wc), free(wc_lst), 1);
		ft_lstclear(wc_lst, del_node_wc);
		free(wc_lst);
		return (0);
	}
	free(wc_lst);
	return (0);
}

int expand_wc(char *cmd, t_expand *expand)
{
	t_wildcard	*wc;

	wc = get_wc_line(cmd);
	if (!wc)
		return (1);
	printf_wc(wc);
	if (expand_wc_content(wc, expand->tmp))
		return (1);
	return (0);
}
