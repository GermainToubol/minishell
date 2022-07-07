/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 01:01:16 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/07 22:12:46 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "utils.h"
#include "libft.h"

void	printf_wc(t_wildcard *mywc)
{
	if (mywc->dir_path)
		ft_printf("\tpath: %s\n", mywc->dir_path);
	if (mywc->found)
		ft_printf("\tfound: %s\n", mywc->found);
	if (mywc->prefix)
		ft_printf("\tprefix: %s\n", mywc->prefix);
	if (mywc->suffix)
		ft_printf("\tsuffix: %s\n\n", mywc->suffix);
}

t_wildcard	*cpy_wc(t_wildcard *wc)
{
	t_wildcard	*new;

	new = ft_calloc(1, sizeof(t_wildcard));
	if (!new)
		return (error_alloc(), NULL);
	new->suffix = NULL;
	new->found = NULL;
	new->prefix = ft_strdup(wc->prefix);
	new->dir_path = ft_strdup(wc->dir_path);
	if (!new->prefix || !new->dir_path)
	{
		del_node_wc(new);
		return (error_alloc(), NULL);
	}
	return (new);
}

static int	dir_path(char *path, t_wildcard *new)
{
	char		cwd_dir[DIR_BUFFER];
	char		*tmp;

	new->dir_path = NULL;
	if (!path)
		new->dir_path = ft_strdup(getcwd(cwd_dir, DIR_BUFFER));
	else if (path[0] == '/')
		new->dir_path = ft_strdup(path);
	else
	{
		tmp = ft_strjoin("/", path);
		free(path);
		if (strjoin_custom(&(new->dir_path), tmp))
			return (1);
	}
	if (!new->dir_path)
		return (error_alloc(), 1);
	return (0);
}

t_wildcard	*init_wc(char *path, char *prefix, char *suffix)
{
	t_wildcard	*new;

	new = ft_calloc(1, sizeof(t_wildcard));
	if (!new)
		return (error_alloc(), NULL);
	new->found = NULL;
	new->prefix = ft_strdup(prefix);
	new->suffix = trim_c(suffix, '/');
	if (dir_path(path, new) || !new->suffix || !new->prefix)
	{
		del_node_wc(new);
		return (error_alloc(), NULL);
	}
	return (new);
}
