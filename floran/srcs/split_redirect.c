/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:32:15 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/09 23:29:27 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "floran.h"

static int	has_word(char *str)
{
	if (*str == '>')
		str++;
	while (ft_iswhitspaces(*str))
		str++;
	if (!*str)
		return (error_msg("syntax error near unexpected \
token `newline'", NO_EXIT, 2), 0);
	if (*str == '<')
		return (error_msg("syntax error near unexpected \
token `<'", NO_EXIT, 2), 0);
	if (*str == '>')
		return (error_msg("syntax error near unexpected \
token `>'", NO_EXIT, 2), 0);
	return (1);
}

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
			if (j > 0 && str[j - 1] == '<')
				j++;
			else
			{
				if (!has_word(&str[++j]))
					return (-1);
				w++;
			}
		}
	}
	return (w);
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
			j = 1;
			while (i - j >= 0 && ft_isdigit(str[i - j]))
				j++;
			if (j > 1)
				tab[k] = fill_redirect(&str[i + 1], sep,
						ft_substr(str, i - j, j));
			else
				tab[k] = fill_redirect(&str[i + 1], sep, ft_strdup("1"));
			if (!tab[k++])
				return (free_red(tab));
			if (str[i + 1] == '>')
				i++;
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
	tab = (t_redirect **)malloc((words + 1) * sizeof(t_redirect *));
	if (!tab)
		return (NULL);
	do_split(tab, str, sep);
	return (tab);
}
