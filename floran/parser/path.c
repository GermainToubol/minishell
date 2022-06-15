/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:04:40 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/15 16:19:28 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "libft.h"

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

char	*check_path(char **path, char *cmd)
{
	int		i;
	char	*path_cmd;

	i = -1;
	if (access(cmd, X_OK) != -1)
		return (cmd);
	if (ft_strchr(cmd, '/') != NULL)
		return (NULL);
	while (path[++i])
	{
		path_cmd = ft_join3(path[i], "/", cmd);
		if (!path_cmd)
			return (0);
		if (access(path_cmd, X_OK) != -1)
			return (path_cmd);
		free(path_cmd);
	}
	return (NULL);
}
