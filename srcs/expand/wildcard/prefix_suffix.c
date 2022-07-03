/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefix_suffix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:47:30 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/30 19:18:49 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "utils.h"

static t_wildcard	*prefix_suffix_content(t_wildcard *mywc,
						char *found, size_t i, size_t i2)
{
	size_t	k;

	while (found[i2])
	{
		k = 0;
		while (found[k + i2] && mywc->suffix[i + k]
			&& mywc->suffix[i + k] == found[k + i2])
			k++;
		if (mywc->suffix[i + k] == '*')
			return (new_wc(mywc, found, i + k, i2 + k));
		if (mywc->suffix[i + k] == '/' && found[k + i2] == '\0')
			return (new_wc_path(mywc, found, i + k, i2 + k));
		if (mywc->suffix[i + k] == '\0' && found[i2 + k] == '\0')
			return (new_wc(mywc, found, i + k, i2 + k));
		i2++;
	}
	return (NULL);
}

t_wildcard	*prefix_suffix(t_wildcard *mywc, char *found)
{
	size_t		i;
	size_t		i2;

	i = last_char(mywc->prefix, '/');
	i++;
	if (ft_strncmp(&mywc->prefix[i], found, ft_strlen(&mywc->prefix[i])))
		return (NULL);
	i2 = 0;
	while (mywc->prefix[i + i2] != '\0' && mywc->prefix[i + i2] == found[i2])
		i2++;
	i = 0;
	if (mywc->suffix[i] == '/')
		return (new_wc_path(mywc, found, i, 0));
	while (mywc->suffix[i] == '*')
		i++;
	if (mywc->suffix[i] == '\0' || mywc->suffix[i] == '/')
		return (new_wc(mywc, found, i, ft_strlen(found)));
	return (prefix_suffix_content(mywc, found, i, i2));
}
