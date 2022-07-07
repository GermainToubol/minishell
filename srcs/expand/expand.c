/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:46:41 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/07 22:12:46 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "expand.h"
#include "libft.h"
#include "utils.h"

static int	do_expand_loop(char **cmd, t_list **lst)
{
	size_t		i;
	t_list		**lst_tmp;
	t_expand	expand;

	i = 0;
	lst_tmp = ft_calloc(1, sizeof(t_list *));
	if (!lst_tmp)
		return (error_alloc(), 1);
	*lst_tmp = NULL;
	expand.saved = lst;
	expand.tmp = lst_tmp;
	while (cmd[i])
	{
		expand.line = cmd[i];
		expand.next = 0;
		if (expand_loop(&expand))
			return (free_lst_str(lst_tmp), 1);
		i++;
	}
	free_lst_str(lst_tmp);
	return (0);
}

char	**do_expand(char **cmd)
{
	char	**ret;
	t_list	**lst;

	lst = ft_calloc(1, sizeof(t_list *));
	if (!lst)
		return (error_alloc(), NULL);
	*lst = NULL;
	if (do_expand_loop(cmd, lst))
		return (free_lst_str(lst), NULL);
	if (!lst)
		return (NULL);
	ret = lst_to_tab_str(lst);
	free_lst_str(lst);
	return (ret);
}
