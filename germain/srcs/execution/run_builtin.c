/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:14:29 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/22 16:27:30 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <unistd.h>
#include "libft.h"
#include "parser.h"
#include "minishell.h"
#include "g_minishell.h"

static void	builtin_set_pipe(int *pipe_in, int *pipe_out);
static void	builtin_close_fds(t_parse *parse);
static void	*get_builtin(t_parse *parse);

int	run_builtin(t_parse *parse, t_list **env, int *pipe_in, int *pipe_out)
{
	int	i;
	int	status;
	int	stdin_cpy;
	int	stdout_cpy;
	int	(*f)(int, char **, t_list **);

	stdin_cpy = dup(0);
	stdout_cpy = dup(1);
	status = 0;
	builtin_set_pipe(pipe_in, pipe_out);
	if (do_redirect(parse) != 0)
		return (1);
	i = 0;
	while (parse->cmd->cmd[i] != NULL)
		i++;
	f = get_builtin(parse);
	status = (*f)(i, parse->cmd->cmd, env);
	builtin_close_fds(parse);
	dup2(stdin_cpy, STDIN_FILENO);
	dup2(stdout_cpy, STDOUT_FILENO);
	close(stdin_cpy);
	close(stdout_cpy);
	return (status);
}

static void	*get_builtin(t_parse *parse)
{
	char	*name;

	name = parse->cmd->cmd[0];
	if (ft_strcmp(name, "echo") == 0)
		return (builtin_echo);
	if (ft_strcmp(name, "cd") == 0)
		return (builtin_cd);
	if (ft_strcmp(name, "pwd") == 0)
		return (builtin_pwd);
	if (ft_strcmp(name, "export") == 0)
		return (builtin_export);
	if (ft_strcmp(name, "unset") == 0)
		return (builtin_unset);
	if (ft_strcmp(name, "env") == 0)
		return (builtin_env);
	return (builtin_exit);
}

static void	builtin_set_pipe(int *pipe_in, int *pipe_out)
{
	if (pipe_in[0] != -2)
		close(pipe_in[1]);
	if (pipe_out[0] != -2)
		close(pipe_out[0]);
	if (pipe_in[0] != -2)
		dup2(pipe_in[0], STDIN_FILENO);
	if (pipe_out[0] != -2)
		dup2(pipe_out[1], STDOUT_FILENO);
	if (pipe_in[0] != -2)
		close(pipe_in[0]);
	if (pipe_out[0] != -2)
		close(pipe_out[1]);
}

static void	builtin_close_fds(t_parse *parse)
{
	int			i;
	t_redirect	**redirect;

	i = 0;
	redirect = parse->cmd->redirect;
	while (redirect != NULL && redirect[i] != NULL)
	{
		close(redirect[i]->fd);
		i++;
	}
}
