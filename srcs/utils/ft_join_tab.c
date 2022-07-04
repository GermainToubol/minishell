/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:57:35 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/04 01:57:59 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utils.h"

static int	ft_join_tab_content(char **tab1, size_t size_tab[2],
				char **tab2, char ***ret)
{
	size_t	size;

	size = -1;
	while (++size < size_tab[0])
	{
		(*ret)[size] = ft_strdup(tab1[size]);
		if (!(*ret)[size])
			return (free_tab((*ret)), 1);
	}
	size = -1;
	while (++size < size_tab[1])
	{
		(*ret)[size + size_tab[0]] = ft_strdup(tab2[size]);
		if (!(*ret)[size + size_tab[0]])
			return (free_tab((*ret)), 1);
	}
	(*ret)[size_tab[0] + size] = NULL;
	return (0);
}

int	ft_join_tab(char ***tab1, size_t size1, char **tab2, size_t size2)
{
	char	**ret;
	size_t	size;
	size_t	size_tab[2];

	size_tab[0] = size1;
	size_tab[1] = size2;
	size = size1 + size2;
	if (size == 0)
		return (1);
	ret = ft_calloc(size + 1, sizeof(char *));
	if (!ret)
		return (display_error("Error allocation\n", 0), 1);
	if (ft_join_tab_content(*tab1, size_tab, tab2, &ret))
		return (display_error("Error allocation\n", 0), 1);
	free_tab(*tab1);
	*tab1 = ret;
	return (0);
}
