/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 03:33:06 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/22 03:58:34 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "expand.h"
#include "libft.h"
#include "utils.h"

static char	**alloc_cmd(char **new_cmd, char **ret,
				size_t *size, size_t *max)
{
	size_t	len;

	len = size_tab(ret);
	while (*size + len >= *max)
	{
		*max += TAB_BUFFER;
		new_cmd = tab_realloc(new_cmd, 1, *size, *max);
		if (!new_cmd)
			return (free_tab(ret), NULL);
	}
	if (cpy_tab(ret, &new_cmd[*size], len))
	{
		free_tab(ret);
		free_tab(new_cmd);
		return (NULL);
	}
	*size += size_tab(ret);
	free_tab(ret);
	return (new_cmd);
}

static char	**do_wildcard_content(t_list **wc_lst, char **new_cmd,
				size_t *size, size_t *max)
{
	char	**ret;

	ret = NULL;
	ret = lst_to_tab(wc_lst);
	ft_lstclear(wc_lst, del_node);
	if (!ret)
		return (NULL);
	quicksort(ret, size_tab(ret));
	return (alloc_cmd(new_cmd, ret, size, max));
}

char	**do_wildcard(char *cmd, char ***new_cmd,
				size_t *size, size_t *max)
{
	t_list	**wc_lst;

	wc_lst = ft_calloc(1, sizeof(t_list *));
	if (!wc_lst)
		return (display_error("Error allcation\n", 0), NULL);
	*wc_lst = wildcards(cmd);
	if (*wc_lst)
	{
		new_cmd[*size] = do_wildcard_content(wc_lst, *new_cmd, size, max);
		if (!new_cmd)
			return (NULL);
	}
	else
	{
		(*new_cmd)[*size] = ft_strdup(cmd);
		if (!(*new_cmd)[(*size)++])
			return (display_error("Error allcation\n", 0), NULL);
		new_cmd[*size] = NULL;
	}
	free(wc_lst);
	return (*new_cmd);
}
