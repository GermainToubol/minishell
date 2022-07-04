/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:00:45 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/04 17:31:14 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expand.h"
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

static int	add_c(char c, char **tmp)
{
	size_t	size;
	size_t	i;
	char	*new;

	size = ft_strlen(*tmp);
	size += 2;
	new = ft_calloc(size + 1, sizeof(char));
	if (!new)
		return (1);
	i = 0;
	new[i] = c;
	while ((*tmp)[++i - 1])
		new[i] = (*tmp)[i - 1];
	new[i++] = c;
	new[i] = '\0';
	free(*tmp);
	*tmp = new;
	return (0);
}

static int	rec_do_quotes(const char *cmd, size_t *i,
				char **ret, char *tmp)
{
	char	*tmp2;

	if (cmd[*i] == '\'')
	{

		if (add_c('"', &tmp))
			return (1);
		if (strjoin_custom(ret, tmp))
			return (1);
	}
	else if (cmd[*i] == '"')
	{
		tmp2 = expand_var_quotes(tmp);
		free(tmp);
		if (!tmp2 && strjoin_custom(ret, ft_strdup("")))
			return (1);
		else if (tmp2)
		{
			if (add_c('"', &tmp2))
				return (1);
			if (strjoin_custom(ret, tmp2))
				return (1);
		}
	}
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
	if (*i > start + 1)
	{
		tmp = ft_substr(cmd, start, *i - start);
		if (!tmp)
			return (display_error("Error allocation\n", 0), 1);
		if (rec_do_quotes(cmd, i, ret, tmp))
			return (1);
	}
	else if (strjoin_custom(ret, ft_strdup("")))
		return (1);
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
	{
		if (strjoin_custom(ret, ft_substr(cmd, start, i - start)))
			return (1);
	}
	if (cmd[i] && rec_quote_content(cmd, &i, ret))
		return (1);
	return (0);
}

char	*quotes(const char *cmd)
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
