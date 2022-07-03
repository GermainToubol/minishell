/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:13:25 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/16 11:07:45 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

/**
   Add VAR to the environment.

   @var should be formated as "VAR_NAME=VALUE" str
 */

static t_list	*tmp_add(t_list **lst, t_dico *dico);

t_list	*environment_add(t_list **old_env, char *var)
{
	t_list	*tmp;
	t_dico	*new;
	t_dico	*old_dico;

	new = ft_newdico(var);
	if (new == NULL)
	{
		ft_lstclear(old_env, ft_freedico);
		return (NULL);
	}
	tmp = *old_env;
	while (tmp != NULL)
	{
		old_dico = (t_dico *)tmp->content;
		if (ft_strcmp(old_dico->key, new->key) == 0)
		{
			ft_freedico(old_dico);
			tmp->content = (void *)new;
			return (*old_env);
		}
		tmp = tmp->next;
	}
	return (tmp_add(old_env, new));
}

static t_list	*tmp_add(t_list **lst, t_dico *dico)
{
	t_list	*tmp;

	tmp = ft_lstnew(dico);
	if (tmp == NULL)
	{
		ft_freedico(dico);
		ft_lstclear(lst, ft_freedico);
		return (NULL);
	}
	ft_lstadd_back(lst, tmp);
	return (*lst);
}
