/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand_wc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 13:44:38 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/04 16:46:15 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include "expand.h"
#include "utils.h"

static int	var_expand_wc_content(char ***ret, char *tab)
{
	char	**tmp;

	if (ft_strchr(tab, '*'))
	{
		tmp = expand_wc(tab);
		if (!tmp)
			return (free_tab(*ret), 1);
		if (ft_join_tab(ret, size_tab(*ret), tmp, size_tab(tmp)))
			return (free_tab(*ret), 1);
	}
	else
	{
		if (ft_join_tab(ret, size_tab(*ret), &tab, 1))
			return (free_tab(*ret), 1);
	}
	return (0);
}

int	var_expand_wc(char ***tab)
{
	size_t	i;
	char	**ret;

	i = 0;
	ret = NULL;
	while ((*tab)[i])
	{
		if (var_expand_wc_content(&ret, (*tab)[i]))
			return (1);
		i++;
	}
	if (i == 0)
	{
		ret = ft_calloc(1, sizeof(char *));
		if (!ret)
			return (display_error("Error allocation\n", 0), 1);
		ret[0] = NULL;
	}
	free_tab(*tab);
	*tab = ret;
	return (0);
}
