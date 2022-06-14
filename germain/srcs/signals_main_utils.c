/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_main_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 10:07:07 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/14 17:17:19 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <signal.h>
#include <unistd.h>
#include "minishell.h"
#include "g_minishell.h"

void	kill_from_lst(void *content)
{
	pid_t	pid;

	pid = (pid_t)(long int)content;
	kill(pid, SIGINT);
}
