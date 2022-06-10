/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_clear_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:43:10 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/10 14:00:18 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

static void	clear_pipes(void *content);

void	g_clear_heredocs(t_list	**heredoc_list)
{
	ft_lstclear(heredoc_list, clear_pipes);
}

static void	clear_pipes(void *content)
{
	int	*pipe_fds;

	pipe_fds = (int *)content;
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	free(pipe_fds);
}
