/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:46:41 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/22 03:26:00 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "expand.h"
#include "libft.h"
#include "utils.h"

static char	**do_wildcard_content(t_list **wc_lst, char **new_cmd,
				size_t *size, size_t *max)
{
	char	**ret;
	size_t	len;

	ret = NULL;
	ret = lst_to_tab(wc_lst);
	ft_lstclear(wc_lst, del_node);
	if (!ret)
		return (NULL);
	len = size_tab(ret);
	quicksort(ret, len);
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

static char **do_wildcard(char *cmd, char **new_cmd,
				size_t *size, size_t *max)
{
	t_list	**wc_lst;

	wc_lst = ft_calloc(1, sizeof(t_list *));
	if (!wc_lst)
		return (display_error("Error allcation\n", 0), NULL);
	*wc_lst = wildcards(cmd);
	if (*wc_lst)
	{
		new_cmd = do_wildcard_content(wc_lst, new_cmd, size, max);
		if (!new_cmd)
			return (NULL);
	}
	else
	{
		new_cmd[*size] = ft_strdup(cmd);
		if (!new_cmd[(*size)++])
			return (display_error("Error allcation\n", 0), NULL);
		new_cmd[*size] = NULL;
	}
	free(wc_lst);
	return (new_cmd);
}

static char	**do_expand_loop(char **cmd, char **new_cmd, size_t *max)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (cmd[i])
	{
		if (size >= *max)
		{
			*max += TAB_BUFFER;
			new_cmd = tab_realloc(new_cmd, 1, size, *max);
			if (!new_cmd)
				return (free_tab(new_cmd), NULL);
		}
		if (ft_strchr(cmd[i], '*') != NULL)
		{
			new_cmd = do_wildcard(cmd[i], new_cmd, &size, max);
			if (!new_cmd)
				return (NULL);
		}
		else
		{
			new_cmd[size] = ft_strdup(cmd[i]);
			if (!new_cmd[size++])
				return (display_error("Error allcation\n", 0), NULL);
			new_cmd[size] = NULL;
		}
		i++;
	}
	if (size < *max)
	{
		new_cmd = tab_realloc(new_cmd, -1, size, TAB_BUFFER);
		if (!new_cmd)
			return (NULL);
		new_cmd[size] = NULL;
	}
	return (new_cmd);
}

char	**do_expand(char **cmd)
{
	char	**new_cmd;
	size_t	max;

	max = TAB_BUFFER;
	new_cmd = NULL;
	new_cmd = tab_realloc(new_cmd, 0, 0, TAB_BUFFER);
	new_cmd = do_expand_loop(cmd, new_cmd, &max);
	free_tab(cmd);
	return (new_cmd);
}
