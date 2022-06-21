/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_format.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:27:20 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/16 11:57:31 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

/**
   Set the environment in a NULL terminated char ** format

   @return: env as {KEY=VALUE, ..., NULL} format. NULL on failure.
*/

static char	*tmp_dico_join(t_dico *dico);

char	**environment_format(t_list *env)
{
	size_t	i;
	char	**new_env;

	i = ft_lstsize(env);
	new_env = ft_calloc(i + 1, sizeof(*new_env));
	if (new_env == NULL)
		return (NULL);
	i = 0;
	while (env != NULL)
	{
		new_env[i] = tmp_dico_join(env->content);
		if (new_env[i] == NULL)
		{
			ft_free_split(new_env);
			return (NULL);
		}
		env = env->next;
		i++;
	}
	return (new_env);
}

static char	*tmp_dico_join(t_dico *dico)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	i = ft_strlen(dico->key);
	if (dico->value == NULL)
		new_str = ft_strdup(dico->key);
	else
	{
		j = ft_strlen(dico->value);
		new_str = ft_calloc(i + j + 2, sizeof(*new_str));
		if (new_str == NULL)
			return (NULL);
		ft_strlcat(new_str, dico->key, i + j + 2);
		ft_strlcat(new_str, "=", i + j + 2);
		ft_strlcat(new_str, dico->value, i + j + 2);
	}
	return (new_str);
}
