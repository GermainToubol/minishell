/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefix_suffix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:47:30 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/06 20:43:22 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "utils.h"

static t_wildcard	*prefix_suffix_content(t_wildcard *mywc,
						char *found, size_t i, size_t i2)
{
	size_t	k;

	if (i == 0 && found[i2] != mywc->suffix[i])
		return (NULL);
	while (found[i2])
	{
		k = 0;
		while (found[k + i2] && mywc->suffix[i + k]
			&& mywc->suffix[i + k] == found[k + i2])
			k++;
		if (mywc->suffix[i + k] == '*'
			&& (i + k == 0 || mywc->suffix[i + k - 1] != '\\'))
		{
			return (new_wc(mywc, found, i + k, i2 + k));
		}
		if (mywc->suffix[i + k] == '/' && found[k + i2] == '\0')
			return (new_wc_path(mywc, found, i + k, i2 + k));
		if (mywc->suffix[i + k] == '\0' && found[i2 + k] == '\0')
			return (new_wc(mywc, found, i + k, i2 + k));
		i2++;
	}
	return (NULL);
}

int	match_prefix(t_wildcard *mywc, char *found,
				size_t *i2)
{
	size_t	start;

	start = last_char(mywc->prefix, '/');
	ft_printf("prefix %s\nfound %s\n", &mywc->prefix[start], found);
	if (ft_strncmp(&mywc->prefix[start], found,
		ft_strlen(&mywc->prefix[start])))
		return (1);
	*i2 = 0;
	while (mywc->prefix[start + *i2] != '\0'
		&& mywc->prefix[start + *i2] == found[*i2])
		(*i2)++;
	return (0);
}

t_wildcard	*prefix_suffix(t_wildcard *mywc, char *found)
{
	size_t		i;
	size_t		i2;

	printf_wc(mywc);
	if (!found)
		return (NULL);
	ft_printf("check prefix\n");
	if (match_prefix(mywc, found, &i2))
		return (NULL);
	ft_printf("prefix ok\n");
	i = 0;
	if (mywc->suffix[i] == '/')
	{
		while (mywc->suffix[i] == '/')
			i++;
		return (new_wc_path(mywc, found, i, i2));
	}
	if (mywc->suffix[i] == '*'
			&& (i == 0 || mywc->suffix[i - 1] != '\\'))
	{
		ft_printf("* found\n");
		while (mywc->suffix[i] == '*')
			i++;
	}
	if (mywc->suffix[i] == '\0' || mywc->suffix[i] == '/')
		return (new_wc(mywc, found, i, ft_strlen(found)));
	return (prefix_suffix_content(mywc, found, i, i2));
}
