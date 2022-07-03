/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:57:35 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/03 20:17:10 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utils.h"

static int	ft_join_tab_content(char **tab1, size_t size1, char **tab2, char ***ret)
{
	size_t	size;

	size = -1;
	while (++size < size1)
	{
		(*ret)[size] = ft_strdup(tab1[size]);
		if (!(*ret)[size])
			return (free_tab((*ret)), 1);
	}
	size = -1;
	while (tab2[++size])
	{
		(*ret)[size + size1] = ft_strdup(tab2[size]);
		if (!(*ret)[size + size1])
			return (free_tab((*ret)), 1);
	}
	(*ret)[size1 + size] = NULL;
	return (0);
}

int	ft_join_tab(char ***tab1, size_t size1, char **tab2, size_t size2)
{
	char	**ret;
	size_t	size;

	size = size1 +size2;
	if (size == 0)
		return (1);
	ret = ft_calloc(size + 1, sizeof(char *));
	if (!ret)
		return (display_error("Error allocation\n", 0), 1);
	if (ft_join_tab_content(*tab1, size1, tab2, &ret))
		return (display_error("Error allocation\n", 0), 1);
	free_tab(*tab1);
	*tab1 = ret;
	return (0);
}
