/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_set.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:03:29 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/16 16:04:59 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

/**
   Set the value of the environment variable name to value

   @return: 0 if the value is set, 1 if the key isn't an environment variable,
   -1 otherwise.
*/

int	environment_set(t_list *env, char *name, char *value)
{
	char	*value_str;
	t_dico	*dico;

	value_str = ft_strdup(value);
	if (value_str == NULL)
		return (-1);
	while (env != NULL)
	{
		dico = (t_dico *)env->content;
		if (ft_strcmp(dico->key, name) == 0)
		{
			free(dico->value);
			dico->value = value_str;
			return (0);
		}
		env = env->next;
	}
	return (1);
}
