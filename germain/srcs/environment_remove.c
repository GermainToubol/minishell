/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_remove.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:51:50 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/15 13:54:35 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

char	**environment_remove(char **env, char *name)
{
	size_t	i;
	size_t	name_len;
	int		name_found_flag;

	i = 0;
	name_found_flag = 0;
	name_len = ft_strlen(name);
	while (env[i] != NULL)
	{
		if (name_found_flag == 0 && ft_strncmp(name, env[i], name_len) == 0
			&& env[i][name_len] == '=')
		{
			name_found_flag = 1;
			free(env[i]);
			env[i] = env[i + 1];
		}
		else if (name_found_flag == 1)
			env[i] = env[i + 1];
		i++;
	}
	return (env);
}
