/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 03:47:46 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/03 19:02:42 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "expand.h"
#include "libft.h"
#include "utils.h"

char	**do_basic(char *cmd)
{
	char	**ret;

	if (!cmd)
	{
		ret = ft_calloc(1, sizeof(char *));
		if (!ret)
			return (display_error("Error allocation\n", 0), NULL);
		ret[0] = NULL;
		return (ret);
	}
	ret = ft_calloc(2, sizeof(char *));
	if (!ret)
		return (display_error("Error allocation\n", 0), NULL);
	ret[0] = ft_strdup(cmd);
	ret[1] = NULL;
	if (!ret[0])
	{
		free(ret);
		return (display_error("Error allcation\n", 0), NULL);
	}
	return (ret);
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

static int	expand_loop2(char ***new_cmd, char *cmd, size_t i)
{
	if (ft_strchr(cmd, '*') != NULL)
	{
		new_cmd[i] = expand_wc(cmd);
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

int	expand_loop(char ***new_cmd, char *cmd, size_t i)
{
	char	*tmp;
	char	**tmp2;
	char	**tmp3;

	if (ft_strchr(cmd, '\'') || ft_strchr(cmd, '"'))
	{
		tmp = expand_quotes(cmd);
		if (ft_strchr(cmd, '*') != NULL)
		{
			new_cmd[i] = expand_wc(tmp);
			free(tmp);
			if (!new_cmd[i])
				return (1);
		}
		else
		{
			new_cmd[i] = do_basic(tmp);
			free(tmp);
			if (!new_cmd[i])
				return (1);
		}
	}
	else if (ft_strchr(cmd, '$'))
	{
		tmp = expand_var(cmd);
		tmp2 = ft_split(tmp, ' ');
		free(tmp);
		if (!tmp2)
			return (1);
		tmp3 = expand_wc(tmp2[size_tab(tmp2) - 1]);
		if (!tmp3)
			return (1);
		new_cmd[i] = ft_join_tab(tmp2, size_tab(tmp2), tmp3, size_tab(tmp3));
		if (!new_cmd[i])
			return (1);
	}
	else
		return (expand_loop2(new_cmd, cmd, i));
	return (0);
}
