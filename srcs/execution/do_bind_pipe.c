/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_bind_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 09:18:20 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/22 11:28:30 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include "minishell.h"
#include "g_minishell.h"

int	do_bind_pipe(int *pfd)
{
	int	status;

	status = pipe(pfd);
	if (status != 0)
		perror("minishell: pipe");
	return (status);
}
