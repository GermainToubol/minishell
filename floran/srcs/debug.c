/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:13:53 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/09 23:39:18 by fmauguin         ###   ########.fr       */
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
	i = -1;
	ft_printf("input : %s\noutput :f\tfd\tApp\n", tmp->input);
	if (!tmp->outputs[++i])
		ft_printf("(null)\n");
	else
	{
		while (tmp->outputs[i])
		{
			ft_printf("\t%s\t%i\t%i\n", tmp->outputs[i]->file,
				tmp->outputs[i]->out, tmp->outputs[i]->append);
			i++;
		}
	}
}
