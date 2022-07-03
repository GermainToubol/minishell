/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:17:45 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/22 16:26:13 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "libft.h"
#include "utils.h"

size_t	tab3_size(char ***new_cmd)
{
	size_t	count;
	size_t	i;
	size_t	j;

	count = 0;
	i = 0;
	while (new_cmd[i])
	{
		j = 0;
		while (new_cmd[i][j])
		{
			count++;
			j++;
		}
		i++;
	}
	return (count);
}

void	free_tab3(char ***tab)
{
	size_t	i;

	if (!tab)
		return ;
	if (!*tab)
		return (free(tab));
	i = 0;
	while (tab[i])
		free_tab(tab[i++]);
	free(tab);
}
