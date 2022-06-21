/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefix_suffix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:47:30 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/21 20:53:37 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "utils.h"

static t_wildcard	*new_wc(t_wildcard *mywc, char *found,
						size_t i, size_t i2)
{
	t_wildcard	*new;
	char		*tmp;

	new = ft_calloc(1, sizeof(t_wildcard));
	if (!new)
		return (display_error("Error allocation\n", 0), NULL);
	new->dir_path = ft_strdup(mywc->dir_path);
	new->found = ft_strdup(found);
	tmp = ft_strndup(found, i2);
	new->prefix = ft_strjoin(mywc->prefix, tmp);
	free(tmp);
	if (mywc->suffix[i] == '\0')
		new->suffix = NULL;
	else
	{
		new->suffix = ft_strdup(&mywc->suffix[i]);
		if (!new->suffix)
		{
			del_node(new);
			return (display_error("Error allocation\n", 0), NULL);
		}
	}
	if (!new->dir_path || !new->prefix)
	{
		del_node(new);
		return (display_error("Error allocation\n", 0), NULL);
	}
	return (new);
}

static int	new_wc_path2(t_wildcard *mywc, t_wildcard *new
						, char *tmp, size_t i)
{
	new->prefix = tmp;
	new->suffix = ft_strdup(&mywc->suffix[i + 1]);
	new->dir_path = ft_strdup(mywc->dir_path);
	new->found = NULL;
	if (!new->dir_path || !new->prefix || !new->suffix)
		return (display_error("Error allocation\n", 0), 1);
	return (0);
}

static t_wildcard	*new_wc_path(t_wildcard *mywc, char *found,
						size_t i, size_t i2)
{
	t_wildcard	*new;
	char		*tmp;
	char		*tmp2;

	new = ft_calloc(1, sizeof(t_wildcard));
	if (!new)
		return (display_error("Error allocation\n", 0), NULL);
	tmp2 = ft_substr(found, 0, i2);
	if (!tmp2)
		return (display_error("Error allocation\n", 0), NULL);
	if (mywc->prefix[0] != '\0'
		&& mywc->prefix[ft_strlen(mywc->prefix) - 1] == '/')
		tmp = ft_strjoin(mywc->prefix, tmp2);
	else
		tmp = ft_join3(mywc->prefix, "/", tmp2);
	free(tmp2);
	if (new_wc_path2(mywc, new, tmp, i))
		return (del_node(new), NULL);
	return (new);
}

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
