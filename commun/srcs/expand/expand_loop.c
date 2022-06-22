/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 03:47:46 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/22 03:57:14 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "expand.h"
#include "libft.h"
#include "utils.h"

char	**expand_loop_wildcard(char **new_cmd, char *cmd,
			size_t *size, size_t *max)
{
	if (ft_strchr(cmd, '*') != NULL)
	{
		new_cmd = do_wildcard(cmd, &new_cmd, size, max);
		if (!new_cmd)
			return (NULL);
	}
	else
	{
		new_cmd[*size] = ft_strdup(cmd);
		if (!new_cmd[*size++])
			return (display_error("Error allcation\n", 0), NULL);
		new_cmd[*size] = NULL;
	}
	return (new_cmd);
}

char	**expand_loop_realloc(char **new_cmd, size_t *size,
			size_t *max)
{
	if (*size >= *max)
	{
		*max += TAB_BUFFER;
		new_cmd = tab_realloc(new_cmd, 1, *size, *max);
		if (!new_cmd)
			return (free_tab(new_cmd), NULL);
	}
	return (new_cmd);
}

char	**expand_loop_end(char **new_cmd, size_t *size,
			size_t *max)
{
	if (*size < *max)
	{
		new_cmd = tab_realloc(new_cmd, -1, *size, TAB_BUFFER);
		if (!new_cmd)
			return (NULL);
		new_cmd[*size] = NULL;
	}
	return (new_cmd);
}
