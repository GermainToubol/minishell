/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 16:05:10 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/04 23:52:09 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "utils.h"
#include "expand.h"
#include "g_minishell.h"

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

char	*expand_var_quotes(const char *cmd)
{
	char	*ret;

	ret = NULL;
	if (!ft_strchr(cmd, '$'))
	{
		ret = ft_strdup(cmd);
		if (!ret)
			display_error("Error allocation\n", 0);
	}
	else if (rec_var_q(cmd, 0, &ret))
		return (free(ret), NULL);
	return (ret);
}
