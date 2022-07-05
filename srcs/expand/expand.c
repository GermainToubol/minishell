/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:46:41 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/05 22:56:12 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "expand.h"
#include "libft.h"
#include "utils.h"

static void free_expand(t_expand *expand)
{
	free_lst_str(expand->tmp);
	if (expand->origin)
		free(expand->origin);
}

static int do_expand_loop(char **cmd, t_list **lst)
{
	size_t	i;
	t_list	**lst_tmp;
	t_expand	expand;

	i = 0;
	lst_tmp = ft_calloc(1, sizeof(t_list *));
	if (!lst_tmp)
		return (display_error("Error allocation\n", 0), 1);
	*lst_tmp = NULL;
	expand.saved = lst;
	expand.tmp = lst_tmp;
	while (cmd[i])
	{
		expand.line = cmd[i];
		expand.origin = NULL;
		expand.next = 0;
		expand.has_wc = 0;
		if (expand_loop(&expand))
			return (free_expand(&expand), 1);
		i++;
	}
	free_expand(&expand);
	return (0);
}

char	**do_expand(char **cmd)
{
	char	**ret;
	t_list	**lst;

	lst = ft_calloc(1, sizeof(t_list *));
	if (!lst)
		return (display_error("Error allocation\n", 0), NULL);
	*lst = NULL;
	if (do_expand_loop(cmd, lst))
		return (free_lst_str(lst), NULL);
	if (!lst)
		return (NULL);
	ret = lst_to_tab_str(lst);
	ft_printf("\n\n====================\n\n");
	print_tab(ret);
	ft_printf("\n====================\n\n");
	free_lst_str(lst);
	return (ret);
}
