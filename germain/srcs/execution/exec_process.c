/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 09:24:46 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/28 11:33:19 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "libft.h"
#include "parser.h"
#include "expand.h"
#include "utils.h"
#include "minishell.h"
#include "g_minishell.h"

static char	**new_tab(char **av, int size)
{
	char	**ret;
	int		i;

	ret = ft_calloc(size + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < size)
	{
		if (ft_strchr(av[i], '\'') || ft_strchr(av[i], '"'))
			ret[i] = expand_quotes(av[i]);
		else if (ft_strchr(av[i], '$'))
			ret[i] = expand_var(av[i]);
		else
			ret[i] = ft_strdup(av[i]);
		if (!ret[i] && get_status() != 0)
			return (ft_free_split(ret), NULL);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

int	expand_parse(t_parse *parse)
{
	char	**lst;
	char	**new;
	int		i;

	i = 0;
	while (parse->cmd->cmd[i] != NULL)
		i++;
	lst = new_tab(parse->cmd->cmd, i);
	if (!lst)
		return (1);
	new = do_expand(lst);
	ft_free_split(lst);
	if (!new)
		return (display_error("Error\n", 0), 1);
	ft_free_split(parse->cmd->cmd);
	parse->cmd->cmd = new;
	return (0);
}

pid_t	exec_process(t_parse *parse, t_clean *cleanable,
			int *pipe_in, int *pipe_out)
{
	pid_t	pid;

	if (parse->cmd->cmd != NULL)
		expand_parse(parse);
	if (is_builtin(parse))
		return (-17 - run_builtin(parse, cleanable->env, pipe_in, pipe_out));
	pid = fork();
	if (pid < 0)
		perror("minishell: fork");
	if (pid == 0)
	{
		while (cleanable->n_pipes > 0)
			cleanable_pop_pipe(cleanable);
		run_child(parse, cleanable->env, pipe_in, pipe_out);
		exit(get_status());
	}
	if (pid_extend_list(pid))
		return (-1);
	run_parent(pipe_in);
	return (pid);
}
