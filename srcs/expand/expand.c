/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:46:41 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/04 21:20:11 by fmauguin         ###   ########.fr       */
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
		return (display_error("Error allocation\n", 0), NULL);
	while (cmd[i])
	{
		if (expand_loop(cmd[i], lst, lst_tmp))
			return (NULL);
		i++;
	}

	return (expand_loop_end(lst));
}

char	**do_expand(char **cmd)
{
	t_list	**lst;
	char	**ret;

	lst = ft_calloc(1, sizeof(t_list *));
	if (!lst)
		return (display_error("Error allocation\n", 0), NULL);
	if (do_expand_loop(cmd, lst))
		return (NULL);
	if (!lst || !*lst)
		return (NULL);
	ret = lst_to_tab(lst);
	return (ret);
}
