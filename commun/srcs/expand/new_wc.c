/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_wc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:59:12 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/22 15:11:54 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wildcard.h"
#include "utils.h"

t_wildcard	*new_wc2(t_wildcard *mywc, char *found, char *tmp, size_t i)
{
	t_wildcard	*new;

	new = ft_calloc(1, sizeof(t_wildcard));
	if (!new)
		return (display_error("Error allocation\n", 0), NULL);
	new->dir_path = ft_strdup(mywc->dir_path);
	new->found = ft_strdup(found);
	new->prefix = ft_strjoin(mywc->prefix, tmp);
	if (mywc->suffix[i] != '\0')
		new->suffix = ft_strdup(&mywc->suffix[i]);
	else
		new->suffix = NULL;
	if (!new->dir_path || !new->prefix
		|| (mywc->suffix[i] != '\0' && !new->suffix))
	{
		del_node(new);
		return (display_error("Error allocation\n", 0), NULL);
	}
	return (new);
}

t_wildcard	*new_wc(t_wildcard *mywc, char *found, size_t i, size_t i2)
{
	t_wildcard	*new;
	char		*tmp;

	tmp = ft_strndup(found, i2);
	if (!tmp)
		return (display_error("Error allocation\n", 0), NULL);
	new = new_wc2(mywc, found, tmp, i);
	free(tmp);
	return (new);
}

t_wildcard	*new_wc_path2(t_wildcard *mywc, char *tmp, size_t i)
{
	t_wildcard	*new;

	new = ft_calloc(1, sizeof(t_wildcard));
	if (!new)
	{
		free(tmp);
		return (display_error("Error allocation\n", 0), NULL);
	}
	new->prefix = tmp;
	new->suffix = ft_strdup(&mywc->suffix[i + 1]);
	new->dir_path = ft_strdup(mywc->dir_path);
	new->found = NULL;
	if (!new->dir_path || !new->prefix || !new->suffix)
	{
		del_node (new);
		return (display_error("Error allocation\n", 0), NULL);
	}
	return (new);
}

t_wildcard	*new_wc_path(t_wildcard *mywc, char *found, size_t i, size_t i2)
{
	char		*tmp;
	char		*tmp2;

	tmp2 = ft_substr(found, 0, i2);
	if (!tmp2)
		return (display_error("Error allocation\n", 0), NULL);
	if (mywc->prefix[0] != '\0'
		&& mywc->prefix[ft_strlen(mywc->prefix) - 1] == '/')
		tmp = ft_strjoin(mywc->prefix, tmp2);
	else
		tmp = ft_join3(mywc->prefix, "/", tmp2);
	free(tmp2);
	if (!tmp)
		return (display_error("Error allocation\n", 0), NULL);
	return (new_wc_path2(mywc, tmp, i));
}
