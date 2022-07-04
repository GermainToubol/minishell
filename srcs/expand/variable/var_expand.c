/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 16:05:10 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/04 02:46:41 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "utils.h"
#include "expand.h"
#include "g_minishell.h"

static int	rec_var(const char *cmd, size_t i, char **ret);

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

static int	rec_var_content(const char *cmd, size_t i, char **ret)
{
	size_t	start;
	char	*tmp;

	if (cmd[i] == '\'' || cmd[i] == '"')
	{
		start = i;
		i += (skip_quote(&cmd[i]));
		if (strjoin_custom(ret, ft_substr(cmd, start, i)))
			return (1);
	}
	if (cmd[i] == '$')
	{
		i++;
		if (get_var(cmd, &i, &tmp))
			return (1);
		if (tmp && strjoin_custom(ret, tmp))
			return (1);
	}
	return (rec_var(cmd, i, ret));
}

static int	rec_var(const char *cmd, size_t i, char **ret)
{
	size_t	start;

	if (!cmd[i])
		return (0);
	start = i;
	while (cmd[i] && cmd[i] != '$' && cmd[i] != '"' && cmd[i] != '\'')
		i++;
	if (i > start
		&& strjoin_custom(ret, ft_substr(cmd, start, i - start)))
		return (1);
	if (cmd[i] && rec_var_content(cmd, i, ret))
		return (1);
	return (0);
}

char	**expand_var(const char *cmd)
{
	char	*ret;
	char	**tab_ret;

	ret = NULL;
	if (rec_var(cmd, 0, &ret))
		return (NULL);
	tab_ret = split_var(ret);
	return (tab_ret);
}
