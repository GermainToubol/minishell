/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:14:32 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/10 11:02:45 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "floran.h"

static char	**get_path(char **env)
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

int	get_cmd(char **cmd, char **envp, t_list **l_cmd)
{
	char	**path;
	int		i;

	path = get_path(envp);
	if (!path)
		return (0);
	i = 0;
	*l_cmd = ft_lstnew((void *)fill_cmd_strct(path, cmd[i]));
	if (!*l_cmd)
		return (free_tab(path), 0);
	while (cmd[++i])
		ft_lstadd_back(l_cmd, ft_lstnew((void *)fill_cmd_strct(path, cmd[i])));
	free_tab(path);
	free_tab(cmd);
	return (1);
}
