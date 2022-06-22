/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefix_suffix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:47:30 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/22 15:00:04 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "utils.h"

static t_wildcard	*prefix_suffix_content(t_wildcard *mywc,
						char *found, size_t i, size_t i2)
{
	size_t	k;

	if (mywc->suffix[i] == '/')
		return (new_wc_path(mywc, found, i, 0));
	while (mywc->suffix[i] == '*')
		i++;
	if (mywc->suffix[i] == '\0' || mywc->suffix[i] == '/')
		return (new_wc(mywc, found, i, ft_strlen(found)));
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
	i2 = 0;
	while (mywc->prefix[i] && found[i2] && mywc->prefix[i] == found[i2])
	{
		i++;
		i2++;
	}
	if (mywc->prefix[i] != found[i2] && mywc->prefix[i] && !found[i2])
		return (NULL);
	return (prefix_suffix_content(mywc, &found[i2], 0, 0));
}
