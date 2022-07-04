/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 16:05:10 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/04 16:05:13 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "utils.h"
#include "expand.h"
#include "g_minishell.h"

static int	rec_var(const char *cmd, size_t i, char ***ret, size_t *size);
static int	rec_var_q(const char *cmd, size_t i, char **ret);

static int	rec_var_q_content(const char *cmd, size_t i, char **ret)
{
	size_t	start;
	char	*tmp;

	if (cmd[i] == '\'' || cmd[i] == '"')
	{
		start = i;
		i += (skip_quote(&cmd[i]));
		if (strjoin_custom(ret, ft_substr(cmd, start, i - start)))
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
	return (rec_var_q(cmd, i, ret));
}

static int	rec_var_q(const char *cmd, size_t i, char **ret)
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
	if (cmd[i] && rec_var_q_content(cmd, i, ret))
		return (1);
	return (0);
}

static int	var_tab(char *tmp, char ***ret, size_t *size)
{
	char	**tmp2;
	char	*old_ret;
	size_t	tab_len;

	tmp2 = split_var(tmp);
	if (!tmp2)
		return (1);
	tab_len = size_tab(tmp2);
	if (!(*ret)[*size])
		(*ret)[*size] = ft_strdup(tmp2[0]);
	else
	{
		old_ret = ft_strjoin(((*ret)[*size]), tmp2[0]);
		free((*ret)[*size]);
		(*ret)[*size] = old_ret;
	}
	if (!(*ret)[*size])
		return (free_tab(tmp2), 1);
	if (ft_join_tab(ret, *size + 1, &tmp2[1], tab_len - 1))
		return (free_tab(tmp2), 1);
	*size = size_tab(*ret) - 1;
	return (0);
}

static int	rec_var_content(const char *cmd, size_t i,
				char ***ret, size_t *size)
{
	size_t	start;
	char	*tmp;

	if (cmd[i] == '\'' || cmd[i] == '"')
	{
		start = i;
		i += (skip_quote(&cmd[i]));
		tmp = ft_substr(cmd, start, i - start);
		if (strjoin_custom(&(*ret)[*size], expand_quotes(tmp)))
			return (free(tmp), 1);
		free(tmp);
	}
	if (cmd[i] == '$')
	{
		i++;
		if (get_var(cmd, &i, &tmp))
			return (1);
		if (tmp && !ft_strchr(tmp, ' ') && strjoin_custom(&(*ret)[*size], tmp))
			return (1);
		else if (tmp && ft_strchr(tmp, ' ') && var_tab(tmp, ret, size))
			return (1);
		print_tab(*ret);
	}
	return (rec_var(cmd, i, ret, size));
}

static int	rec_var(const char *cmd, size_t i, char ***ret, size_t *size)
{
	size_t	start;

	if (!cmd[i])
		return (0);
	start = i;
	while (cmd[i] && cmd[i] != '$' && cmd[i] != '"' && cmd[i] != '\'')
		i++;
	if (i > start
		&& strjoin_custom(&(*ret)[*size], ft_substr(cmd, start, i - start)))
		return (1);
	if (cmd[i] && rec_var_content(cmd, i, ret, size))
		return (1);
	return (0);
}

char	**expand_var(const char *cmd)
{
	char	**ret;
	size_t	size;

	ret = ft_calloc(2, sizeof(char *));
	if (!ret)
		return (display_error("Error allocation\n", 0), NULL);
	ret[0] = NULL;
	ret[1] = NULL;
	size = 0;
	if (rec_var(cmd, 0, &ret, &size))
		return (free_tab(ret), NULL);
	return (ret);
}

char	*expand_var_quotes(const char *cmd)
{
	char	*ret;

	ret = NULL;
	if (rec_var_q(cmd, 0, &ret))
		return (free(ret), NULL);
	return (ret);
}
