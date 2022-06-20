/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 01:01:16 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/20 02:18:28 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "utils.h"

void	printf_wc(t_wildcard *mywc)
{
	if (mywc->dir_path)
		ft_printf("\tpath: %s\n", mywc->dir_path);
	if (mywc->prefix)
		ft_printf("\tprefix: %s\n", mywc->prefix);
	if (mywc->suffix)
		ft_printf("\tsuffix: %s\n\n", mywc->suffix);
}

static t_wildcard	*new_wc(t_wildcard *mywc, char *found,
						size_t i, size_t i2)
{
	t_wildcard	*new;

	new = ft_calloc(1, sizeof(t_wildcard));
	if (!new)
		return (display_error("Error allocation\n", 0), NULL);
	new->dir_path = ft_strdup(mywc->dir_path);
	new->prefix = ft_substr(found, 0, i2);
	if (mywc->suffix[i] == '*')
		new->suffix = ft_strdup(&mywc->suffix[i + 1]);
	else
		new->suffix = ft_strdup("");
	if (!new->dir_path || !new->prefix || !new->suffix)
		return (display_error("Error allocation\n", 0), NULL);
	return (new);
}

t_wildcard	*prefix_suffix(t_wildcard *mywc, char *found)
{
	size_t		i;
	size_t		i2;

	i = 0;
	i2 = 0;
	while (mywc->prefix[i] && found[i2] && mywc->prefix[i] == found[i2])
	{
		i++;
		i2++;
	}
	if (mywc->prefix[i] != found[i2] && mywc->prefix[i])
		return (NULL);
	while (found[i2])
	{
		i = 0;
		while (found[i2 + i] && mywc->suffix[i]
				&& mywc->suffix[i] == found[i2 + i])
			i++;
		if (mywc->suffix[i] == '*')
		{
			if (mywc->suffix[i + 1] == '\0')
				return (new_wc(mywc, found, i, ft_strlen(found)));
			return (new_wc(mywc, found, i, i2));
		}
		if (mywc->suffix[i] == '\0' && found[i2 + i] == '\0')
			return (new_wc(mywc, found, i, i2 + i));
		i2++;
	}
	return (NULL);
}

t_wildcard	*init_wc(void)
{
	t_wildcard	*new;
	char 		cwd_dir[DIR_BUFFER];

	new = ft_calloc(1, sizeof(t_wildcard *));
	if (!new)
		return (display_error("Error allocation\n", 0), NULL);
	new->dir_path = ft_strdup(getcwd(cwd_dir, DIR_BUFFER));
	new->suffix = ft_strdup("");
	new->prefix = ft_strdup("");
	if (!new->dir_path || !new->prefix || !new->suffix)
		return (display_error("Error allocation\n", 0), NULL);
	return (new);
}
