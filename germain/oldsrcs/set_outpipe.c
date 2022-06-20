/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_outpipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:53:15 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/20 10:07:05 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include "minishell.h"
#include "g_minishell.h"

int	set_outpipe(int *pipe_fds)
{
	if (pipe(pipe_fds) != 0)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}
