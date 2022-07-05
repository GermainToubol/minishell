/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 00:38:09 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/30 15:00:37 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "libft.h"
#include "utils.h"

void	free_lxm(t_lxm *lxm, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		free(lxm[i++].data);
	free(lxm);
}

void	free_tab(char **tab)
{
	size_t	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i++]);
	}
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

void	free_cmd(t_cmd	*tmp)
{
	if (!tmp)
		return ;
	if (tmp->path_exec)
		free(tmp->path_exec);
	free_tab(tmp->cmd);
	free_red(tmp->redirect);
	free (tmp);
}

void	free_parse(t_parse **parse)
{
	size_t	i;

	i = 0;
	if (!parse)
		return ;
	if (del_hdoc_parse(parse))
		return ;
	while (parse[i])
	{
		free_cmd(parse[i]->cmd);
		free(parse[i++]);
	}
	free(parse);
}

void	free_parse_nohdoc(t_parse **parse)
{
	size_t	i;

	i = 0;
	if (!parse)
		return ;
	while (parse[i])
	{
		free_cmd(parse[i]->cmd);
		free(parse[i++]);
	}
	free(parse);
}
