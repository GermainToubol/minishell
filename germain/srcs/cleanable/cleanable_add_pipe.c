/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanable_add_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 11:58:31 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/28 12:02:21 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "g_minishell.h"

void	cleanable_add_pipe(t_clean *cleanable, int *pipe_fds)
{
	if (pipe_fds[0] != -2)
	{
		cleanable->pipe[2 * cleanable->n_pipes] = pipe_fds[0];
		cleanable->pipe[2 * cleanable->n_pipes + 1] = pipe_fds[1];
		cleanable->n_pipes += 1;
	}
}
