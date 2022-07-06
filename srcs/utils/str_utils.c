/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:42:57 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/07 00:03:08 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "expand.h"
#include "libft.h"
#include "utils.h"

size_t	last_char(char *s, char c)
{
	size_t	i;
	size_t	r;

	i = 0;
	r = 0;
	while (s[i])
	{
		if (s[i] == c)
			r = i + 1;
		i++;
	}
	return (r);
}

size_t	size_tab(char **tab)
{
	size_t	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
	{
		i++;
	}
	return (i);
}
