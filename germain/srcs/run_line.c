/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:33:43 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/14 16:40:14 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

void	run_line(char *line, char **env)
{
	t_list	*execline;

	(void)line;
	execline = tmp_init_exec();
	run_pipe_series(execline, env);
}
