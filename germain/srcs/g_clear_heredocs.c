/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_clear_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:43:10 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/10 18:11:47 by gtoubol          ###   ########.fr       */
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
	char	*filename;

	filename = (char *)content;
	free(filename);
}
