/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_get.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:53:35 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/16 11:15:01 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

/**
   Get the content of the environment variable NAME

   @return: the content if NAME is in env, NULL otherwise.
*/

char	*environment_get(t_list *env, char *name)
{
	t_dico	*tmp_dico;

	while (env != NULL)
	{
		tmp_dico = (t_dico *)env->content;
		if (ft_strcmp(tmp_dico->key, name) == 0)
			return (tmp_dico->value);
		env = env->next;
	}
	return (NULL);
}
