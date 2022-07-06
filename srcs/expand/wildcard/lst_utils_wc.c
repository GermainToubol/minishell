/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_wc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 22:54:11 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/07 00:31:46 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "libft.h"

void	del_node_wc(void *data)
{
	t_wildcard	*s;

	if (!data)
		return ;
	s = (t_wildcard *)data;
	if (s->dir_path)
		free(s->dir_path);
	if (s->prefix)
		free(s->prefix);
	if (s->suffix)
		free(s->suffix);
	if (s->found)
		free(s->found);
	free(s);
}

void	print_node_wc(void	*data)
{
	t_wildcard	*s;

	s = (t_wildcard *)data;
	ft_printf("\x1b[94m%s/\x1b[0m", s->dir_path);
	ft_printf("\x1b[92m\t%s\x1b[0m", s->prefix);
	ft_printf("\x1b[91m\t\t%s\x1b[0m\n", s->suffix);
}
