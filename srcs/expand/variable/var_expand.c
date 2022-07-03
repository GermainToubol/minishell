/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 16:05:10 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/30 02:44:21 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "utils.h"

static int	get_var(const char *cmd, size_t *i, char **ret)
{
	char	*var;
	size_t	start;

	start = *i;
	if (ft_isdigit(cmd[*i]) && (*i)++)
		return (*ret = NULL, 0);
	while (ft_isalnum(cmd[*i]) || cmd[*i] == '_')
		(*i)++;
	var = ft_substr(cmd, start, *i - start);
	if (!var)
		return (display_error("Error allocation\n", 0), 1);
	*ret = getenv(var);
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

char	*expand_var(const char *cmd)
{
	char	*ret;

	ret = NULL;
	if (!ft_strchr(cmd, '$'))
	{
		ret = ft_strdup(cmd);
		if (!ret)
			display_error("Error allocation\n", 0);
		return (ret);
	}
	if (rec_var(cmd, 0, &ret))
	{
		if (ret)
			free(ret);
		return (NULL);
	}
	return (ret);
}
