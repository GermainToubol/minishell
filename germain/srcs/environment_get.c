/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_get.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:53:35 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/15 15:01:27 by gtoubol          ###   ########.fr       */
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

char	*environment_get(char **env, char *name)
{
	size_t	i;
	size_t	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while (env[i] != NULL)
	{
		if (ft_strncmp(name, env[i], name_len) == 0
			&& env[i][name_len] == '=')
			return (env[i] + name_len + 1);
		i++;
	}
	return (NULL);
}
