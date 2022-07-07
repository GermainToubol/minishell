/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 00:34:48 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/07 22:12:46 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "utils.h"

static void	count_c(char *s, size_t *count, size_t *i, char c)
{
	*count = 0;
	*i = -1;
	if (c == '\\')
	{
		while (s[++(*i)])
			if (s[(*i)] == '\\' && s[(*i) + 1] && s[(*i) + 1] == '*')
				(*count)++;
	}
	else if (c == '*')
	{
		while (s[++(*i)])
			if (s[(*i)] == '*')
				(*count)++;
	}
	else
	{
		while (s[++(*i)])
			if (s[*i] == '*' && *i > 0 && s[*i - 1] == '\\')
				(*count)++;
	}
}

int	clean_backslash(char **s)
{
	size_t	count;
	size_t	i;
	char	*ret;

	if (!s || !*s)
		return (1);
	count_c(*s, &count, &i, '\\');
	ret = ft_calloc(i - count + 1, sizeof(char));
	if (!ret)
		return (error_alloc(), 1);
	i = -1;
	count = 0;
	while ((*s)[++i + count])
	{
		if ((*s)[i + count] == '\\'
			&& (*s)[i + 1 + count] && (*s)[i + 1 + count] == '*')
			count++;
		ret[i] = (*s)[i + count];
	}
	ret[i] = '\0';
	free(*s);
	*s = ret;
	return (0);
}

int	clean_backslash_expand(char *s, t_list *index)
{
	size_t	count;
	size_t	i;
	char	*ret;

	if (!s || !index)
		return (1);
	count_c(s, &count, &i, '\\');
	ret = ft_calloc(i - count + 1, sizeof(char));
	if (!ret)
		return (error_alloc(), 1);
	i = -1;
	count = 0;
	while (s[++i + count])
	{
		if (s[i + count] == '\\'
			&& s[i + 1 + count] && s[i + 1 + count] == '*')
			count++;
		ret[i] = s[i + count];
	}
	ret[i] = '\0';
	free(index->content);
	index->content = ret;
	return (0);
}

char	*add_backslash(char *s)
{
	size_t	count;
	size_t	i;
	char	*ret;

	if (!s)
		return (NULL);
	count_c(s, &count, &i, '*');
	ret = ft_calloc(i + count + 1, sizeof(char));
	if (!ret)
		return (error_alloc(), NULL);
	i = -1;
	count = 0;
	while (s[++i])
	{
		if (s[i] == '*')
			ret[i + count++] = '\\';
		ret[count + i] = s[i];
	}
	ret[count + i] = '\0';
	return (ret);
}

char	*add_backslash_var(char **s)
{
	size_t	count;
	size_t	i;
	char	*ret;

	if (!s || !*s)
		return (NULL);
	count_c(*s, &count, &i, 'q');
	ret = ft_calloc(i + count + 1, sizeof(char));
	if (!ret)
		return (error_alloc(), NULL);
	i = -1;
	count = 0;
	while ((*s)[++i])
	{
		if ((*s)[i] == '*' && i > 0 && (*s)[i - 1] == '\\')
			ret[i + count++] = '\\';
		ret[count + i] = (*s)[i];
	}
	ret[count + i] = '\0';
	free(*s);
	return (ret);
}
