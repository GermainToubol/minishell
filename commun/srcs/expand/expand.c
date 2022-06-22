/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:46:41 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/22 03:48:39 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "expand.h"
#include "libft.h"
#include "utils.h"

static char	**do_expand_loop(char **cmd, char **new_cmd, size_t *max)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (cmd[i])
	{
		new_cmd = expand_loop_realloc(new_cmd, &size, max);
		if (!new_cmd)
			return (NULL);
		new_cmd = expand_loop_wildcard(new_cmd, cmd[i], &size, max);
		if (!new_cmd)
			return (NULL);
		i++;
	}
	return (expand_loop_end(new_cmd, &size, max));
}

char	**do_expand(char **cmd)
{
	char	**new_cmd;
	size_t	max;

	max = TAB_BUFFER;
	new_cmd = NULL;
	new_cmd = tab_realloc(new_cmd, 0, 0, TAB_BUFFER);
	new_cmd = do_expand_loop(cmd, new_cmd, &max);
	free_tab(cmd);
	return (new_cmd);
}
