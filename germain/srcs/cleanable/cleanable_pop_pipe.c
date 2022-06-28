/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanable_pop_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 12:03:20 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/28 12:07:10 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "minishell.h"
#include "g_minishell.h"

void	cleanable_pop_pipe(t_clean *cleanable)
{
	int	n;

	n = cleanable->n_pipes;
	if (n > 0)
	{
		close(cleanable->pipe[2 * n]);
		close(cleanable->pipe[2 * n + 1]);
		cleanable->n_pipes--;
	}
}
