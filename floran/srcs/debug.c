/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:13:53 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/09 16:25:40 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "floran.h"

void	print_node(void *data)
{
	t_cmd	*tmp;
	int		i;

	tmp = NULL;
	tmp = (struct s_cmd *)data;
	if (!tmp)
		return ;
	ft_printf("\nPath_exec : %s\ncmd :", tmp->path_exec);
	i = -1;
	while (tmp->cmd[++i])
		ft_printf("\t%s\n", tmp->cmd[i]);
	ft_printf("input : %s\noutput : %s\nerrput : \
%s\n", tmp->input, tmp->output, tmp->errput);
	ft_printf("heredoc : %i\nappend : %i\n\n",
		tmp->heredoc, tmp->append);
}
