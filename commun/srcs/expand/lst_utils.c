/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 22:54:11 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/21 17:50:07 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

int	strncmp_sep(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	i_s2;

	if (*s2 == '\0')
		return (0);
	len_s1 = ft_strlen(s1);
	i_s2 = 0;
	while (s2[i_s2] && s2[i_s2] != '*')
		i_s2++;
	i_s2--;
	len_s1--;
	while (len_s1 > 0 && i_s2 > 0 && s1[len_s1] == s2[i_s2])
	{
		len_s1--;
		i_s2--;
	}
	if (s1[len_s1] == s2[i_s2])
		return (0);
	return (1);
}

void	del_node(void *data)
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

void	free_ptr(void *data)
{
	if (!data)
		return ;
	free(data);
}

void	print_lst2(void	*data)
{
	t_wildcard	*s;

	s = (t_wildcard *)data;
	ft_printf("\x1b[94m%s/\x1b[0m", s->dir_path);
	ft_printf("\x1b[92m%s\x1b[0m", s->prefix);
	ft_printf("\x1b[91m\t\t%s\x1b[0m\n", s->suffix);
}
