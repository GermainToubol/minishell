/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 09:24:46 by gtoubol           #+#    #+#             */
/*   Updated: 2022/07/04 15:15:11 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "libft.h"
#include "parser.h"
#include "expand.h"
#include "utils.h"
#include "minishell.h"
#include "g_minishell.h"

int	expand_parse(t_parse *parse)
{
	char	**lst;
	char	**new;
	int		i;

	i = 0;
	while (parse->cmd->cmd[i] != NULL)
		i++;
	lst = parse->cmd->cmd;
	if (!lst)
		return (1);
	new = do_expand(lst);
	ft_free_split(lst);
	if (!new)
		return (display_error("Error\n", 0), 1);
	parse->cmd->cmd = new;
	return (0);
}

pid_t	exec_process(t_parse *parse, t_clean *cleanable,
			int *pipe_in, int *pipe_out)
{
	pid_t	pid;

	if (parse->cmd == 0)
		return (set_status(get_status()), -17);
	if (parse->cmd->cmd == NULL)
		return (-17);
	if (expand_parse(parse) != 0)
		return (-1);
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
		clear_cleanable(cleanable);
		exit(get_status());
	}
	if (pid_extend_list(pid))
		return (set_status(-1), -1);
	run_parent(pipe_in);
	return (unset_father(), pid);
}
