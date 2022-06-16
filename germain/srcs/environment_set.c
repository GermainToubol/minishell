/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_set.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:03:29 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/15 18:25:51 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

static char	*set_new_variable(char *name, char *value);

char	**environment_set(char **env, char *name, char *value)
{
	size_t	i;
	size_t	name_len;
	char	*new;

	i = 0;
	name_len = ft_strlen(name);
	new = set_new_variable(name, value);
	if (new == NULL)
	{
		ft_free_split(env);
		return (NULL);
	}
	while (env[i] != NULL)
	{
		if (ft_strncmp(name, env[i], name_len) == 0
			&& (env[i][name_len] == '=' || env[i][name_len] == '\0'))
		{
			free(env[i]);
			env[i] = new;
			return (env);
		}
		i++;
	}
	env = environment_add(new);
	return (env);
}

static char	*set_new_variable(char *name, char *value)
{
	char	*new;
	size_t	total_size;

	total_size = ft_strlen(name) + ft_strlen(value) + 2;
	new = ft_calloc(total_size, sizeof(*new));
	if (new == NULL)
		return (NULL);
	ft_strlcat(new, name, total_size);
	ft_strlcat(new, "=", total_size);
	ft_strlcat(new, value, total_size);
	return (new);
}
