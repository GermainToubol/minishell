/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 01:16:22 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/04 02:12:37 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "utils.h"

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

static size_t	count_line(const char *line)
{
	size_t	count;
	size_t	i;

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

static int	fill_split_content(const char *line,
				char ***ret, size_t *i, size_t *count)
{
	if (line[*i + 1] == '\0')
	{
		(*i)++;
		(*ret)[*count] = ft_substr(line, 0, *i);
		if (!(*ret)[(*count)++])
			return (free_tab((*ret)), 1);
	}
	else
		(*i)++;
	return (0);
}

static int	fill_split(const char *line, char ***ret)
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
		else if (fill_split_content(line, ret, &i, &count))
			return (1);
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
