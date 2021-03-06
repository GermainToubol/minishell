/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_hdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:46:09 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/07 22:12:46 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "libft.h"
#include "utils.h"

static int	rec_quote(const char *cmd, size_t i, char **ret);

static size_t	i_matching_quote(const char *cmd, size_t start)
{
	char	quote;

	quote = cmd[start];
	while (cmd[++start])
		if (cmd[start] == quote)
			return (start);
	return (0);
}

static int	rec_do_quotes(const char *cmd, size_t *i,
				char **ret, char *tmp)
{
	if (cmd[*i] == '\'' && strjoin_custom(ret, tmp))
		return (1);
	else if (cmd[*i] == '"' && strjoin_custom(ret, tmp))
		return (1);
	return (0);
}

static int	rec_quote_content(const char *cmd, size_t *i, char **ret)
{
	size_t	start;
	char	*tmp;

	start = *i;
	*i = i_matching_quote(cmd, start);
	if (*i == 0)
		return (1);
	start++;
	if (*i != start)
	{
		tmp = ft_substr(cmd, start, *i - start);
		if (!tmp)
			return (error_alloc(), 1);
		if (rec_do_quotes(cmd, i, ret, tmp))
			return (1);
	}
	if (rec_quote(cmd, *i + 1, ret))
		return (1);
	return (0);
}

static int	rec_quote(const char *cmd, size_t i, char **ret)
{
	size_t	start;

	if (!cmd[i])
		return (0);
	start = i;
	while (cmd[i] && cmd[i] != '\'' && cmd[i] != '"')
		i++;
	if (i > start)
		if (strjoin_custom(ret, ft_substr(cmd, start, i - start)))
			return (1);
	if (cmd[i] && rec_quote_content(cmd, &i, ret))
		return (1);
	return (0);
}

char	*quotes_hdoc(const char *cmd)
{
	char	*ret;

	ret = NULL;
	if (rec_quote(cmd, 0, &ret))
	{
		if (ret)
			free(ret);
		return (NULL);
	}
	return (ret);
}
