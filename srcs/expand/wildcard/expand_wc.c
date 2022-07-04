/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 03:33:06 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/05 01:47:37 by fmauguin         ###   ########.fr       */
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

t_wildcard	*get_wc_line(const char *cmd, t_list **lst_tmp, size_t *next)
{
	char	*str[3];
	char	*line;
	int		delimiter;

	*next = 1;
	str[0] = NULL;
	str[1] = NULL;
	if (lst_tmp && *lst_tmp)
	{
		line = (char *)ft_lstlast(*lst_tmp)->content;
		delimiter = last_char(line, '/');
		if (delimiter < 0 && strjoin_custom(&str[1], ft_strdup(line)))
			return (NULL);
		else
		{
			if (strjoin_custom(&str[0], ft_substr(line, 0, delimiter + 1)))
				return (NULL);
			if (strjoin_custom(&str[1], ft_substr(line, delimiter + 1,
				ft_strlen(line) - delimiter - 1)))
				return (free(str[0]), NULL);
		}
	}
	*next = to_next_index(&cmd[*next]);
	(*next)++;
	str[2] = NULL;
	if (strjoin_custom(&str[2], ft_substr(cmd, 0, *next)))
		return (free(str[0]), free(str[1]), NULL);
	return (init_wc_2(str[0], str[1], str[2]));
}

int expand_wc(const char *cmd, t_list **lst_tmp, size_t *next)
{
	t_list		**wc_lst;
	t_wildcard	*tmp;

	tmp = get_wc_line(cmd, lst_tmp, next);
	if (!tmp)
		return (1);
	wc_lst = ft_calloc(1, sizeof(t_list *));
	if (!wc_lst)
		return (display_error("Error allcation\n", 0), 1);
	if (wildcards_wc(tmp, wc_lst))
	{
		ft_lstclear(wc_lst, del_node_wc);
		return (free(wc_lst), 1);
	}
	if (*wc_lst)
	{
		ft_lstclear(lst_tmp, del_node_str);
		if (cpy_lst_wc_to_str(lst_tmp, wc_lst))
			return (ft_lstclear(wc_lst, del_node_wc), free(wc_lst), 1);
		sort_list(lst_tmp);
		ft_lstclear(wc_lst, del_node_wc);
	}
	free(wc_lst);
	return (0);
}
