/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_copy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:01:15 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/15 12:28:45 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

/**
   Duplicate the environment to be able to add/modify/remove variable.
 */

char	**environment_copy(char **env)
{
	size_t	i;
	char	**new_env;
	char	*new_var;

	i = 0;
	while (env[i] != NULL)
		i++;
	new_env = ft_calloc(i + 1, sizeof(*new_env));
	if (new_env == NULL)
		return (NULL);
	i = 0;
	while (env[i] != NULL)
	{
		new_var = ft_strdup(env[i]);
		if (new_var == NULL)
		{
			ft_free_split(new_env);
			return (NULL);
		}
		new_env[i] = new_var;
		i++;
	}
	return (new_env);
}
