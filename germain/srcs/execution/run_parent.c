/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_parent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:59:19 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/22 14:13:38 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "minishell.h"
#include "g_minishell.h"

void	run_parent(int *pipe_in)
{
	if (pipe_in[0] != -2)
	{
		close(pipe_in[0]);
		close(pipe_in[1]);
	}
	pipe_in[0] = -2;
	pipe_in[1] = -2;
}
