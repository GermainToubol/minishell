/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_bash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:32:15 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/10 14:27:09 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "floran.h"

int	is_sep(char c, char *sep)
{
	int	i;
	int	l;

	l = ft_strlen(sep);
	i = -1;
	while (++i <= l)
		if (c == sep[i])
			return (1);
	return (0);
}

static int	count_w(char *str, char *sep)
{
	int	w;
	int	i;

	i = -1;
	w = 0;
	while (*str)
	{
		if (!is_sep(*str, sep))
		{
			i = -1;
			w++;
			while (!is_sep(*str, sep))
				str++;
			if (!*str)
				break ;
		}
		str++;
		if (!*str)
			w++;
	}
	return (w);
}

static int	do_split2(char **tab, int *i, char *str)
{
	if (!*str)
	{
		tab[*i] = ft_strdup("");
		if (!tab[(*i)++])
			return (0);
	}
	return (1);
}

static void	do_split(char **tab, char *str, char *sep)
{
	int	j;
	int	i;

	i = 0;
	while (*str)
	{
		if (!is_sep(*str, sep))
		{
			j = 0;
			while (!is_sep(str[j], sep))
				j++;
			tab[i] = ft_strndup(str, j);
			if (!tab[i++])
				return (free_tab(tab));
			str += j;
			if (!*str)
				break ;
		}
		str++;
		if (!do_split2(tab, &i, str))
			return (free_tab(tab));
	}
	tab[i] = NULL;
}

char	**split_sep(char *str, char *sep)
{
	int		words;
	char	**tab;

	words = count_w(str, sep);
	if (words == -1)
		return (NULL);
	tab = (char **)malloc((words + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	do_split(tab, str, sep);
	return (tab);
}
