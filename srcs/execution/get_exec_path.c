/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 09:54:00 by gtoubol           #+#    #+#             */
/*   Updated: 2022/07/04 12:14:42 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <errno.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include "libft.h"
#include "parser.h"
#include "utils.h"
#include "minishell.h"
#include "g_minishell.h"

static int	check_path_relativ(char *cmd_name, t_parse *parse);
static int	check_path_env(char *cmd_name, t_parse *parse, t_list **env);

int	get_exec_path(t_parse *parse, t_list **env)
{
	char	*cmd_name;

	cmd_name = parse->cmd->cmd[0];
	if (cmd_name == NULL)
		return (set_status(0), 1);
	if (ft_strchr(cmd_name, '/') != NULL
		|| environment_get(*env, "PATH") == NULL
		|| environment_get(*env, "PATH")[0] == '\0')
		return (check_path_relativ(cmd_name, parse));
	return (check_path_env(cmd_name, parse, env));
}

static int	check_path_relativ(char *cmd_name, t_parse *parse)
{
	char	*name;

	if (access(cmd_name, X_OK) == 0)
	{
		name = ft_strdup(cmd_name);
		if (name == NULL)
		{
			ft_fprintf(2, "minishell: memory allocation error\n");
			return (set_status(1), 1);
		}
		parse->cmd->path_exec = name;
		return (0);
	}
	ft_fprintf(2, "%s: %s: %s\n", "minishell", cmd_name, strerror(errno));
	if (errno == EACCES)
		return (set_status(126), 126);
	return (set_status(127), 127);
}

static int	check_fullname(char **paths, char *cmd_name, t_parse *parse)
{
	int		i;
	char	*tmp_path;

	i = 0;
	while (paths[i] != NULL)
	{
		tmp_path = ft_join3(paths[i], "/", cmd_name);
		if (tmp_path == NULL)
		{
			ft_fprintf(2, "minishell: memory allocation error\n");
			return (1);
		}
		if (access(tmp_path, X_OK) == 0)
		{
			parse->cmd->path_exec = tmp_path;
			return (0);
		}
		free(tmp_path);
		i++;
	}
	return (-1);
}

static int	check_path_env(char *cmd_name, t_parse *parse, t_list **env)
{
	char	**paths;
	int		i;

	i = -1;
	if (environment_get(*env, "PATH") != NULL)
	{
		paths = ft_split(environment_get(*env, "PATH"), ':');
		if (paths == NULL)
		{
			ft_fprintf(2, "minishell: memory allocation error\n");
			return (1);
		}
		i = check_fullname(paths, cmd_name, parse);
		ft_free_split(paths);
	}
	if (i == 1 || i == 0)
		return (i);
	if (errno == EACCES)
	{
		ft_fprintf(2, "%s: %s: %s\n", "minishell", cmd_name, strerror(errno));
		return (set_status(126), 126);
	}
	ft_fprintf(2, "minishell: %s: command not found\n", cmd_name);
	return (set_status(127), 127);
}
