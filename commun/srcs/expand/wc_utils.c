/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 01:01:16 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/20 18:56:38 by fmauguin         ###   ########.fr       */
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


t_wildcard	*init_wc(char *line)
{
	t_wildcard	*new;
	char		cwd_dir[DIR_BUFFER];

	new = ft_calloc(1, sizeof(t_wildcard *));
	if (!new)
		return (display_error("Error allocation\n", 0), NULL);
	if (line[0] == '/')
		new->dir_path = ft_strdup("");
	else
		new->dir_path = ft_strdup(getcwd(cwd_dir, DIR_BUFFER));
	new->found = NULL;
	new->suffix = ft_strdup("");
	new->prefix = ft_strdup("");
	if (!new->dir_path || !new->prefix || !new->suffix)
		return (display_error("Error allocation\n", 0), NULL);
	return (new);
}
