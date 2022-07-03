/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:57:35 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/03 19:07:30 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utils.h"

char	**ft_join_tab(char **tab1, size_t size1, char **tab2, size_t size2)
{
	char	**ret;
	size_t	size;

	size = size1 +size2;
	if (size == 0)
		return (NULL);
	ret = ft_calloc(size + 1, sizeof(char *));
	if (!ret)
		return (display_error("Error allocation\n", 0), NULL);
	size = -1;
	while (++size < size1)
	{
		ret[size] = ft_strdup(tab1[size]);
		if (!ret[size])
			return (free_tab(ret), NULL);
	}
	size = -1;
	while (++size < size2)
	{
		ret[size + size1] = ft_strdup(tab2[size]);
		if (!ret[size + size1])
			return (free_tab(ret), NULL);
	}
	ret[size1 + size] = NULL;
	return (ret);
}
