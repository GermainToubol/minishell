/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:13:53 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/09 15:17:19 by fmauguin         ###   ########.fr       */
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
	ft_printf("Path_exec : %s\n\ncmd :\n", tmp->path_exec);
	i = -1;
	while (tmp->cmd[++i])
		ft_printf("%s\n", tmp->cmd[i]);
	ft_printf("\ninput : %s\noutput : %s\nerrput : \
	%s\n\n", tmp->input, tmp->output, tmp->errput);
	ft_printf("heredoc : %i\nappend : %i\n",
		tmp->heredoc, tmp->append);
}
