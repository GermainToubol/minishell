/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:13:53 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/10 11:54:39 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "floran.h"

void	show_redline(t_redirect *red, int type)
{
	if (type == 0)
		ft_printf("\t%s\t%i\t%i\n", red->file,
			red->out, red->heredoc);
	else if (type == 1)
	{
		ft_printf("\t%s\t%i\t%i\n", red->file,
			red->out, red->append);
	}
}

void	show_red(t_redirect **red, int type)
{
	int	i;

	i = -1;
	if (type == 0)
		ft_printf("input :");
	else if (type == 1)
		ft_printf("output :");
	if (!red[++i])
		ft_printf("(null)\n");
	else
	{
		if (type == 0)
			ft_printf("file\tfd\tHere\n");
		else if (type == 1)
			ft_printf("file\tfd\tApp\n");
		while (red[i])
		{
			show_redline(red[i], type);
			i++;
		}
	}
	if (type == 1)
		ft_printf("\n");
}

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
	show_red(tmp->inputs, 0);
	show_red(tmp->outputs, 1);
}
