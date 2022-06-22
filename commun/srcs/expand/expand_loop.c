/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 03:47:46 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/22 16:01:07 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
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

static int	fill_ret(char ***new_cmd, char **ret)
{
	size_t	i;
	size_t	j;
	size_t	count;

	count = 0;
	i = 0;
	while (new_cmd[i])
	{
		j = 0;
		while (new_cmd[i][j])
		{
			ret[count] = ft_strdup(new_cmd[i][j]);
			if (!ret[count++])
				return (display_error("Error allcation\n", 0), 1);
			j++;
		}
		i++;
	}
	ret[count] = NULL;
	return (0);
}

char	**expand_loop_end(char ***new_cmd)
{
	size_t	count;
	char	**ret;

	count = tab3_size(new_cmd);
	ret = ft_calloc(count + 1, sizeof(char *));
	if (!ret)
		return (display_error("Error allcation\n", 0), NULL);
	if (fill_ret(new_cmd, ret))
		return (free_tab(ret), NULL);
	return (ret);
}

int	expand_loop_wildcard(char ***new_cmd, char *cmd, size_t i)
{
	if (ft_strchr(cmd, '*') != NULL)
	{
		new_cmd[i] = do_wildcard(cmd);
		if (!new_cmd[i])
			return (1);
	}
	else
	{
		new_cmd[i] = do_basic(cmd);
		if (!new_cmd[i])
			return (1);
	}
	return (0);
}
