/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:46:41 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/05 02:49:09 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "expand.h"
#include "libft.h"
#include "utils.h"

static int do_expand_loop(char **cmd, t_list **lst)
{
	size_t	i;
	t_list	**lst_tmp;

	i = 0;
	lst_tmp = ft_calloc(1, sizeof(t_list *));
	if (!lst_tmp)
		return (display_error("Error allocation\n", 0), 1);
	*lst_tmp = NULL;
	while (cmd[i])
	{
		if (expand_loop(cmd[i], lst, lst_tmp))
			return (free_lst_str(lst_tmp), 1);
		ft_lstclear(lst_tmp, del_node_str);
		i++;
	}
	free_lst_str(lst_tmp);
	return (0);
}

char	**do_expand(char **cmd)
{
	t_list	**lst;
	char	**ret;

	lst = ft_calloc(1, sizeof(t_list *));
	if (!lst)
		return (display_error("Error allocation\n", 0), NULL);
	*lst = NULL;
	if (do_expand_loop(cmd, lst))
	{
		return (NULL);
	}
	if (!lst)
		return (NULL);
	ret = lst_to_tab_str(lst);
	print_tab(ret);
	free_lst_str(lst);
	return (ret);
}
