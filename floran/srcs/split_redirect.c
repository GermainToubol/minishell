/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:32:15 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/10 11:53:08 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "floran.h"

static int	count_w(char *str, char *sep)
{
	int	w;
	int	j;

	j = -1;
	w = 0;
	while (str[++j])
	{
		if (is_sep(str[j], sep))
		{
			if (j > 0 && str[j - 1] == '<' && sep[0] == '>')
				j++;
			else
			{
				if (str[j + 1] && is_sep(str[j + 1], sep))
					j++;
				w++;
			}
		}
	}
	return (w);
}

static int	do_split2(t_redirect **tab, char *str, char *sep, int i)
{
	int	j;

	j = 1;
	while (i - j >= 0 && ft_isdigit(str[i - j]))
		j++;
	if (j > 1)
		*tab = fill_redirect(&str[i + 1], sep,
				ft_substr(str, i - j, j));
	else
	{
		*tab = fill_redirect(&str[i + 1], sep, ft_strdup("1"));
	}
	if (!(*tab))
		return (0);
	return (1);
}

static void	do_split(t_redirect **tab, char *str, char *sep)
{
	int	j;
	int	i;
	int	k;

	i = -1;
	k = 0;
	while (str[++i])
	{
		if (is_sep(str[i], sep))
		{
			if (!(i > 0 && sep[0] == '>' && str[i - 1] == '<'))
			{
				if (!do_split2(&tab[k], str, sep, i))
					return (free_red(tab));
				if (is_sep(str[i + 1], sep))
					i++;
				k++;
			}
		}
	}
	tab[k] = NULL;
}

t_redirect	**split_red(char *str, char *sep)
{
	int			words;
	t_redirect	**tab;

	words = count_w(str, sep);
	if (words == -1)
		return (NULL);
	tab = (t_redirect **)ft_calloc(words + 1, sizeof(t_redirect *));
	if (!tab)
		return (NULL);
	do_split(tab, str, sep);
	return (tab);
}
