/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 16:05:10 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/03 20:26:51 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "utils.h"
#include "expand.h"
#include "g_minishell.h"

static int	get_var(const char *cmd, size_t *i, char **ret)
{
	char	*var;
	size_t	start;

	start = *i;
	if (ft_isdigit(cmd[*i]) && (*i)++)
		return (*ret = NULL, 0);
	if (cmd[*i] == '?' && (*i)++)
		return (*ret = get_status_str(), 0);
	while (ft_isalnum(cmd[*i]) || cmd[*i] == '_')
		(*i)++;
	var = ft_substr(cmd, start, *i - start);
	if (!var)
		return (display_error("Error allocation\n", 0), 1);
	*ret = environment_get(environment_call(), var);
	free(var);
	if (!*ret)
		return (0);
	*ret = ft_strdup(*ret);
	if (!ret)
		return (display_error("Error allocation\n", 0), 1);
	return (0);
}

static int	rec_var(const char *cmd, size_t i, char **ret)
{
	size_t	start;
	char	*tmp;

	if (!cmd[i])
		return (0);
	start = i;
	while (cmd[i] && cmd[i] != '$')
		i++;
	if (i > start
		&& strjoin_custom(ret, ft_substr(cmd, start, i - start)))
		return (1);
	if (cmd[i])
	{
		i++;
		if (get_var(cmd, &i, &tmp))
			return (1);
		if (tmp && strjoin_custom(ret, tmp))
			return (1);
		if (rec_var(cmd, i, ret))
			return (1);
	}
	return (0);
}

int	var_expand_wc(char ***tab)
{
	size_t	i;
	char	**ret;
	char	**tmp;

	i = 0;
	ret = NULL;
	while ((*tab)[i])
	{
		if (ft_strchr((*tab)[i], '*') && !ft_strchr((*tab)[i], '\'') && !ft_strchr((*tab)[i], '"'))
		{
			tmp = expand_wc((*tab)[i]);
			if (!tmp)
				return (free_tab(ret), 1);
			if (ft_join_tab(&ret, size_tab(ret), tmp, size_tab(tmp)))
				return (free_tab(ret), 1);
		}
		else if (ft_join_tab(&ret, size_tab(ret), &tab[i], 1))
			return (free_tab(ret), 1);
		i++;
	}
	free_tab(*tab);
	*tab = ret;
	return (0);
}

char	**expand_var(const char *cmd)
{
	char	*ret;
	char	**tab_ret;

	ret = NULL;
	tab_ret = NULL;
	if (!ft_strchr(cmd, '$'))
	{
		tab_ret = ft_split(cmd, ' ');
		if (!tab_ret)
			return (display_error("Error allocation\n", 0), NULL);
	}
	else if (rec_var(cmd, 0, &ret))
	{
		if (ret)
			free(ret);
		return (NULL);
		tab_ret = ft_split(ret, ' ');
		if (!tab_ret)
			return (display_error("Error allocation\n", 0), NULL);
		return (tab_ret);
		if (var_expand_wc(&tab_ret))
			return (free_tab(tab_ret), NULL);
	}
	return (tab_ret);
}
