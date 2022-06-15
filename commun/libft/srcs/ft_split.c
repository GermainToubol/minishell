/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:04:51 by gtoubol           #+#    #+#             */
/*   Updated: 2022/05/12 14:21:36 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

static int	split_count_words(char const *s, char c);
static void	split_get_words(char const *s, char c, char **strs);
static void	split_free(char **strs, int n);

char	**ft_split(char const *s, char c)
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
		if (j != 0)
		{
			n += 1;
			i += j;
		}
		else
			i++;
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
		if (j != 0)
		{
			str = ft_substr(s, i, j);
			strs[n] = str;
			n++;
			i += j;
		}
		else
			i++;
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
