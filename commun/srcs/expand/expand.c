/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:46:41 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/22 14:01:58 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "expand.h"
#include "libft.h"
#include "utils.h"

static char	**do_expand_loop(char **cmd, char ***new_cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		if (expand_loop_wildcard(new_cmd, cmd[i], i))
			return (NULL);
		i++;
	}
	new_cmd[i] = NULL;
	return (expand_loop_end(new_cmd));
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

char	**do_expand(char **cmd)
{
	char	***new_cmd;
	char	**ret;

	new_cmd = ft_calloc(size_tab(cmd) + 1, sizeof(char **));
	if (!new_cmd)
		return (display_error("Error allocation\n", 0), NULL);
	ret = do_expand_loop(cmd, new_cmd);
	free_tab3(new_cmd);
	return (ret);
}
