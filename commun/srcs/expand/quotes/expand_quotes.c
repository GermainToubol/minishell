/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:46:09 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/26 18:37:32 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "libft.h"
#include "utils.h"

size_t i_matching_quote(const char *cmd, size_t start)
{
	char	quote;

	quote = cmd[start];
	while(cmd[++start])
		if (cmd[start] == quote)
			return (start);
	return (0);
}

static int	rec_quote(const char *cmd, size_t i, char **ret)
{
	size_t	start;
	char	*tmp;

	if (!cmd[i])
		return (0);
	start = i;
	while (cmd[i] && cmd[i] != '\'' && cmd[i] != '"')
		i++;
	if (i > start)
	{
		tmp = ft_substr(cmd, start, i - start);
		if (!tmp)
			return (display_error("Error allocation\n", 0), 1);
		if (strjoin_custom(ret, expand_var(tmp)))
			return (free(tmp), 1);
		free(tmp);
	}
	if (cmd[i])
	{
		start = i;
		i = i_matching_quote(cmd, start);
		if (i == 0)
			return (1);
		start++;
		if (i != start)
		{
			tmp = ft_substr(cmd, start, i - start);
			if (!tmp)
				return (display_error("Error allocation\n", 0), 1);
			if (cmd[i] == '\'' && strjoin_custom(ret, tmp))
				return (1);
			else if (strjoin_custom(ret, expand_var(tmp)))
				return (free(tmp), 1);
			else
				free(tmp);
		}
		if (rec_quote(cmd, i + 1, ret))
			return (1);
	}
	return (0);
}

char	*expand_quotes(const char *cmd)
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