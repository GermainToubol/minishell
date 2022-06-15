/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:13:25 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/15 12:48:07 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

/**
   Add VAR to the environment.

   #var should be formated as "VAR_NAME=VALUE" str
 */

char	**environment_add(char **old_env, char *var)
{
	size_t	i;
	char	**new_env;

	i = 0;
	while (old_env[i] != NULL)
		i++;
	new_env = ft_calloc(i + 2, sizeof(*new_env));
	i = 0;
	while (old_env[i] != NULL)
	{
		new_env[i] = old_env[i];
		i++;
	}
	free(old_env);
	new_env[i] = ft_strdup(var);
	if (new_env[i] == NULL)
	{
		ft_free_split(new_env);
		return (NULL);
	}
	return (new_env);
}
