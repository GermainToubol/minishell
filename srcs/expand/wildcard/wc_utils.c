/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 01:01:16 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/05 18:47:55 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "utils.h"

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
		return (display_error("Error allocation\n", 0), NULL);
	new->suffix = NULL;
	new->found = NULL;
	new->prefix = ft_strdup(wc->prefix);
	new->dir_path = ft_strdup(wc->dir_path);
	if (!new->prefix || !new->dir_path)
	{
		del_node_wc(new);
		return (display_error("Error allocation\n", 0), NULL);
	}
	return (new);
}

t_wildcard	*init_wc(char *line)
{
	t_wildcard	*new;
	char		cwd_dir[DIR_BUFFER];

	new = ft_calloc(1, sizeof(t_wildcard));
	if (!new)
		return (display_error("Error allocation\n", 0), NULL);
	if (line[0] == '/')
		new->dir_path = ft_strdup("");
	else
	{
		new->dir_path = ft_strdup(getcwd(cwd_dir, DIR_BUFFER));
	}
	new->found = NULL;
	new->suffix = ft_strdup("");
	new->prefix = ft_strdup("");
	if (!new->dir_path || !new->prefix || !new->suffix)
	{
		del_node_wc(new);
		return (display_error("Error allocation\n", 0), NULL);
	}
	return (new);
}

static int dir_path(char *path, t_wildcard *new)
{
	char		cwd_dir[DIR_BUFFER];
	char		*tmp;

	new->dir_path = NULL;
	if (!path)
		new->dir_path = ft_strdup(getcwd(cwd_dir, DIR_BUFFER));
	else if (path[0] == '/')
		new->dir_path = path;
	else
	{
		tmp = ft_strjoin("/", path);
		free(path);
		if (strjoin_custom(&(new->dir_path), tmp))
			return (1);
	}
	return (0);
}

t_wildcard	*init_wc_2(char *path, char *prefix, char *suffix)
{
	t_wildcard	*new;

	suffix = trim_c(suffix, '/');
	if (!suffix)
		return (display_error("Error allocation\n", 0), NULL);
	new = ft_calloc(1, sizeof(t_wildcard));
	if (!new)
		return (display_error("Error allocation\n", 0), NULL);
	if (dir_path(path, new))
	{
		del_node_wc(new);
		return (display_error("Error allocation\n", 0), NULL);
	}
	new->found = NULL;
	new->suffix = suffix;
	new->prefix = prefix;
	return (new);
}