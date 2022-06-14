/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:36:20 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/14 14:14:43 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

int	exec_processes(char *line, char **env)
{
	t_list	*execute;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror()
	}
}
