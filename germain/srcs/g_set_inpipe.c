/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_set_inpipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:28:21 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/10 17:29:47 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

int	g_set_inpipe(t_list *execline, int *inpipe, t_list **heredoc_list)
{
	t_cmd		*cmd;
	int			i;
	t_redirect	**inputs;
	t_list		*tmp;

	i = 0;
	tmp = *heredoc_list;
	cmd = (t_cmd *)execline->content;
	inputs = cmd->inputs;
	while (inputs != NULL && inputs[i] != NULL)
	{
		if (inputs[i]->heredoc == IS_HEREDOC)
		{
			if (inpipe[0] >= 0)
			{
				close(inpipe[0]);
				close(inpipe[1]);
			}
			inpipe[0] = ((int *)tmp->content)[0];
			inpipe[1] = ((int *)tmp->content)[1];
			ft_fprintf(2, "%d -- %d\n", inpipe[0], inpipe[1]);
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}
