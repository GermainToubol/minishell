/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathsplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 09:54:00 by gtoubol           #+#    #+#             */
/*   Updated: 2022/07/04 12:14:42 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "g_minishell.h"

static int	split_count_words(char const *s, char c);
static void	split_get_words(char const *s, char c, char **strs);
static void	split_free(char **strs, int n);

char	**ft_pathsplit(const char *s, char c)
{
	char	**strs;
	int		n;
	int		i;

	if (!s)
		return (NULL);
	n = split_count_words(s, c);
	strs = (char **)ft_calloc(n + 1, sizeof(strs));
	if (!strs)
		return (NULL);
	split_get_words(s, c, strs);
	i = 0;
	while (i < n)
	{
		if (strs[i] == NULL)
		{
			split_free(strs, n);
			return (NULL);
		}
		i++;
	}
	return (strs);
}

static int	split_count_words(char const *s, char c)
{
	int	n;
	int	i;
	int	j;

	n = 0;
	i = 0;
	while (s[i] != '\0')
	{
		j = 0;
		while (s[i + j] && s[i + j] != c)
			j++;
		if (j == 0)
			i++;
		if (j == 0 && !(s[i] == '\0' || s[i] == c))
			continue ;
		n += 1;
		i += j;
	}
	return (n);
}

static void	split_get_words(char const *s, char c, char **strs)
{
	char	*str;
	int		i;
	int		j;
	int		n;

	i = 0;
	n = 0;
	while (s[i] != 0)
	{
		j = 0;
		while (s[i + j] && s[i + j] != c)
			j++;
		if (j == 0)
			i++;
		if (j == 0 && !(s[i + 1] == '\0' || s[i + 1] == c))
			continue ;
		str = ft_substr(s, i, j);
		strs[n] = str;
		n++;
		i += j;
	}
	strs[n] = NULL;
}

static void	split_free(char **strs, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}
