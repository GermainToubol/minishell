/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:20:17 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/10 11:53:27 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "floran.h"

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	if (!tab)
		return ;
	while (tab[++i] != NULL)
		free(tab[i]);
	free(tab);
}

void	free_red(t_redirect **tab)
{
	int	i;

	i = -1;
	if (!tab)
		return ;
	while (tab[++i] != NULL)
	{
		if (tab[i]->file)
			free(tab[i]->file);
		free(tab[i]);
	}
	free(tab);
}

void	free_node(void *data)
{
	t_cmd	*tmp;

	tmp = NULL;
	tmp = (struct s_cmd *)data;
	if (!tmp)
		return ;
	if (tmp->path_exec)
		free(tmp->path_exec);
	free_tab(tmp->cmd);
	free_red(tmp->outputs);
	free_red(tmp->inputs);
	free (tmp);
}
