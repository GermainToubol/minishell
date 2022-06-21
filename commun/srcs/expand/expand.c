/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:46:41 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/22 01:50:21 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "expand.h"
#include "libft.h"
#include "utils.h"

static int	do_wildcard_content(t_list	**wc_lst, char **new_cmd,
				size_t *size, size_t *max)
{
	char	**ret;

	ret = NULL;
	ret = lst_to_tab(wc_lst);
	print_tab(ret);
	ft_lstclear(wc_lst, del_node);
	free(wc_lst);
	if (!ret)
		return (1);
	quicksort(ret, size_tab(ret));
	while (*size + size_tab(ret) < *max)
	{
		new_cmd = tab_realloc(new_cmd, 1, TAB_BUFFER);
		if (!new_cmd)
			return (free_tab(ret), 1);
		*max += TAB_BUFFER;
	}
	if (cpy_tab(ret, &new_cmd[*size]))
	{
		free_tab(ret);
		free_tab(new_cmd);
		return (1);
	}
	*size += size_tab(ret);
	free_tab(ret);
	return (0);
}

static int	do_wildcard(char *cmd, char **new_cmd, size_t *size, size_t *max)
{
	t_list	**wc_lst;

	wc_lst = ft_calloc(1, sizeof(t_list *));
	if (!wc_lst)
		return (display_error("Error allcation\n", 0), 1);
	*wc_lst = wildcards(cmd);
	ft_printf("cmd : %s\n", cmd);
	if (*wc_lst)
	{
		ft_printf("here\n");
		if (do_wildcard_content(wc_lst, new_cmd, size, max))
			return (1);
	}
	else
	{
		new_cmd[*size] = ft_strdup(cmd);
		if (!new_cmd[*size++])
			return (display_error("Error allcation\n", 0), 1);
	}
	return (0);
}

static int	do_expand_loop(char **cmd, char **new_cmd, size_t *max)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '*') != NULL)
		{
			if (do_wildcard(cmd[i], new_cmd, &size, max))
				return (1);
		}
		else
		{
			new_cmd[size] = ft_strdup(cmd[i]);
			if (!new_cmd[size++])
				return (display_error("Error allcation\n", 0), 1);
		}
		i++;
	}
	new_cmd = tab_realloc(new_cmd, -1, TAB_BUFFER);
	if (!new_cmd)
		return (1);
	new_cmd[size_tab(new_cmd)] = NULL;
	return (0);
}

char	**do_expand(char **cmd)
{
	char	**new_cmd;
	size_t	max;

	max = TAB_BUFFER;
	new_cmd = NULL;
	new_cmd = tab_realloc(new_cmd, 0, TAB_BUFFER);
	if (do_expand_loop(cmd, new_cmd, &max))
		return (free_tab(cmd), NULL);
	free_tab(cmd);
	return (new_cmd);
}
