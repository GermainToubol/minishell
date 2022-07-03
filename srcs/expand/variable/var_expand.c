/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 16:05:10 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/04 00:30:14 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "utils.h"
#include "expand.h"
#include "g_minishell.h"

static int	rec_var(const char *cmd, size_t i, char **ret);

size_t	skip_quote(const char *line)
{
	size_t	i;
	char	c;

	if (!line)
		return (0);
	c = line[0];
	i = 0;
	while (line[++i])
	{
		if (line[i] == c)
			return (i + 1);
	}
	return (0);
}

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

// int	var_expand_wc(char ***tab)
// {
// 	size_t	i;
// 	char	**ret;
// 	char	**tmp;

// 	i = 0;
// 	ret = NULL;
// 	while ((*tab)[i])
// 	{
// 		if (ft_strchr((*tab)[i], '*') && !ft_strchr((*tab)[i], '\'') && !ft_strchr((*tab)[i], '"'))
// 		{
// 			tmp = expand_wc((*tab)[i]);
// 			if (!tmp)
// 				return (free_tab(ret), 1);
// 			if (ft_join_tab(&ret, size_tab(ret), tmp, size_tab(tmp)))
// 				return (free_tab(ret), 1);
// 		}
// 		else if (ft_join_tab(&ret, size_tab(ret), tab[i], 1))
// 			return (free_tab(ret), 1);
// 		i++;
// 	}
// 	free_tab(*tab);
// 	*tab = ret;
// 	return (0);
// }

// char	**expand_var(const char *cmd)
// {
// 	char	*ret;
// 	char	**tab_ret;

// 	ret = NULL;
// 	tab_ret = NULL;
// 	if (!ft_strchr(cmd, '$'))
// 	{
// 		tab_ret = ft_split(cmd, ' ');
// 		if (!tab_ret)
// 			return (display_error("Error allocation\n", 0), NULL);
// 	}
// 	else if (rec_var(cmd, 0, &ret))
// 	{
// 		if (ret)
// 			free(ret);
// 		return (NULL);
// 	}
// 	ft_printf("expand: %s\n\n", ret);
// 	tab_ret = ft_split(ret, ' ');
// 	if (!tab_ret)
// 		return (display_error("Error allocation\n", 0), NULL);
// 	if (var_expand_wc(&tab_ret))
// 		return (free_tab(tab_ret), NULL);
// 	return (tab_ret);
// }
size_t	count_line(const char *line)
{
	size_t count;
	size_t i;

	if (!line)
		return (0);
	count = 1;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
			i += skip_quote(&line[i]);
		if (line[i] == ' ')
		{
			count++;
			while (line[i] == ' ')
				i++;
			if (!line[i])
				count--;
		}
		else
			i++;
	}
	return (i);
}

int	fill_split(const char *line, char ***ret)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
			i += skip_quote(&line[i]);
		if (line[i] == ' ')
		{
			(*ret)[count] = ft_substr(line, 0, i);
			if (!(*ret)[count++])
				return (free_tab((*ret)), 1);
			while (line[i] == ' ')
				i++;
			line += i;
			i = 0;
		}
		else if (line[i + 1] == '\0')
		{
			i++;
			(*ret)[count] = ft_substr(line, 0, i);
			if (!(*ret)[count++])
				return (free_tab((*ret)), 1);
		}
		else
			i++;
	}
	(*ret)[count] = NULL;
	return (0);
}

char	**split_var(const char *cmd)
{
	size_t	line;
	char	**ret;

	line = count_line(cmd);
	ret = ft_calloc(line + 1, sizeof(char *));
	if (!ret)
		return (display_error("Error allocation\n", 0), NULL);
	if (!line)
		ret[0] = NULL;
	else if (fill_split(cmd, &ret))
		return (display_error("Error allocation\n", 0), NULL);
	return (ret);
}

char	**expand_var(const char *cmd)
{
	char	*ret;
	char	**tab_ret;

	ret = NULL;
	if (rec_var(cmd, 0, &ret))
		return (NULL);
	ft_printf("ret: %s\n", ret);
	tab_ret = split_var(ret);
	print_tab(tab_ret);
	return (tab_ret);
}
