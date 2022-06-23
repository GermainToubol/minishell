/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_copy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:01:15 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/22 19:00:44 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

/**
   Duplicate the environment to be able to add/modify/remove variable.
*/

static void	tmp_free(t_list *tmp, t_list **lst, t_dico *dico);

t_list	*environment_copy(char **env)
{
	size_t	i;
	t_list	*lst;
	t_list	*tmp;
	t_dico	*dico;

	lst = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		tmp = NULL;
		dico = ft_newdico(env[i]);
		if (dico == NULL)
			break ;
		tmp = ft_lstnew(dico);
		if (tmp == NULL)
			break ;
		ft_lstadd_front(&lst, tmp);
		i++;
	}
	tmp_free(tmp, &lst, dico);
	return (lst);
}

static void	tmp_free(t_list *tmp, t_list **lst, t_dico *dico)
{
	if (tmp == NULL)
	{
		if (dico != NULL)
			ft_freedico(dico);
		ft_lstclear(lst, ft_freedico);
		*lst = NULL;
	}
}
