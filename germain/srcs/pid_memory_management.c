/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_memory_management.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:47:10 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/14 17:56:47 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

static t_list	*g_pid_list = NULL;

/**
 * extend_pid_list:
 * append a new pid to the list of pid_processes.
 * #TODO: Error management in extend_pid
 */

void	extend_pid_list(pid_t pid)
{
	t_list	*new;

	new = ft_lstnew((void *)(long int)pid);
	ft_lstadd_back(&g_pid_list, new);
}

/**
 * free_pid_list:
 * removde the given pid from the list of the running pids.
 *
 */

void	free_pid_list(pid_t	pid)
{
	t_list	*tmp;
	t_list	*prev;

	prev = NULL;
	tmp = g_pid_list;
	while (tmp != NULL)
	{
		if ((pid_t)(long int)tmp->content == pid)
		{
			if (prev == NULL)
				g_pid_list = tmp->next;
			else
				prev->next = tmp->next;
			ft_lstdelone(tmp, NULL);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	send_sig_list(void)
{
	ft_lstiter(g_pid_list, kill_from_lst);
}
