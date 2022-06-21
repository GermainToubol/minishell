/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:42:57 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/22 01:46:43 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "expand.h"
#include "libft.h"
#include "utils.h"

int	last_char(char *s, char c)
{
	size_t	i;
	int		r;

	i = 0;
	r = -1;
	while (s[i])
	{
		if (s[i] == c)
			r = (int)i;
		i++;
	}
	return (r);
}

size_t	size_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		i++;
	}
	return (i);
}

int	cpy_tab(char **from, char **to)
{
	size_t	i;

	i = 0;
	while (from[i])
	{
		to[i] = ft_strdup(from[i]);
		if (!to[i])
			return (display_error("Error allcation\n", 0), 1);
		i++;
	}
	to[i] = NULL;
	return (0);
}

static char	**do_realloc(size_t tab_size, char **tab)
{
	char	**tmp;

	tmp = ft_calloc(tab_size + 1, sizeof(char *));
	if (!tmp)
		return (display_error("Error allcation\n", 0), NULL);
	if (cpy_tab(tab, tmp))
	{
		free_tab(tmp);
		free_tab(tab);
		return (NULL);
	}
	return (tmp);
}

char	**tab_realloc(char **tab, int i, size_t buffer_size)
{
	char	**tmp;

	if (i == 0)
	{
		tmp = ft_calloc(buffer_size + 1, sizeof(char *));
		if (!tmp)
			return (display_error("Error allcation\n", 0), NULL);
		return (tmp);
	}
	else if (i > 0)
		tmp = do_realloc(size_tab(tab) + buffer_size, tab);
	else
		tmp = do_realloc(size_tab(tab), tab);
	return (tmp);
}
