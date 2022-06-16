/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:04:40 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/16 13:22:58 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "libft.h"
#include "utils.h"

char	**get_path(char **env)
{
	char	*path;
	char	**ret;
	int		i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", L_PATH) == 0)
		{
			path = ft_strdup(&env[i][L_PATH]);
			if (!path)
				return (NULL);
			ret = ft_split(path, ':');
			free(path);
			if (!ret)
				return (NULL);
			break ;
		}
	}
	return (ret);
}

int	check_path(char **path, char *cmd, char **dest)
{
	int		i;

	i = -1;
	*dest = ft_strdup(cmd);
	if (!*dest)
		return (display_error("Error allocation\n", 0), -1);
	if (access(*dest, X_OK) != -1)
		return (0);
	if (ft_strchr(*dest, '/') != NULL)
	{
		free(*dest);
		return (*dest = NULL, 1);
	}
	free(*dest);
	while (path[++i])
	{
		*dest = ft_join3(path[i], "/", cmd);
		if (!*dest)
			return (display_error("Error allocation\n", 0), -1);
		if (access(*dest, X_OK) != -1)
			return (0);
		free(*dest);
	}
	*dest = NULL;
	return (1);
}
