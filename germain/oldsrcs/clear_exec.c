/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:32:38 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/14 16:34:36 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

void	clear_exec(t_list **execline, pid_t pid)
{
	if (pid > 0)
		ft_lstpop(execline, tmp_free_cmd);
	else
		ft_lstclear(execline, tmp_free_cmd);
}
