/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_remove.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:51:50 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/22 18:59:03 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

void	environment_remove(t_list **env, char *name)
{
	t_list	*tmp;
	t_list	*prev;
	t_dico	*dico;

	prev = NULL;
	tmp = *env;
	while (tmp != NULL)
	{
		dico = (t_dico *)tmp->content;
		if (ft_strcmp(dico->key, name) == 0)
		{
			if (prev == NULL)
				*env = tmp->next;
			else
				prev->next = tmp->next;
			ft_lstdelone(tmp, ft_freedico);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
