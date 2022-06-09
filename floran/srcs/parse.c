/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:14:32 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/09 15:57:57 by fmauguin         ###   ########.fr       */
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

t_cmd	*fill_cmd_strct(char **path, char *cmd)
{
	t_cmd	*data;

	data = (t_cmd *)malloc(sizeof(t_cmd));
	if (!data)
		return (NULL);
	data->cmd = path;
	data->path_exec = ft_strdup(cmd);
	data->append = NO_APPEND;
	data->heredoc = NO_HEREDOC;
	data->input = NULL;
	data->output = NULL;
	data->errput = NULL;
	return (data);
}

int	get_cmd(char **av, char **envp, t_list **l_cmd)
{
	char	**path;
	int		i;

	path = get_path(envp);
	if (!path)
		return (0);
	i = 0;
	*l_cmd = ft_lstnew((void *)fill_cmd_strct(path, av[i]));
	if (!*l_cmd)
		return (0);
	return (1);
}
