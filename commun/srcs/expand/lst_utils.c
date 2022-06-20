/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 22:54:11 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/20 02:31:53 by fmauguin         ###   ########.fr       */
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

	s = (t_wildcard *)data;
	if (s->dir_path)
		free(s->dir_path);
	if (s->prefix)
		free(s->prefix);
	if (s->suffix)
		free(s->suffix);
	free(s);
}

void	ft_list_remove_if(t_list **begin_list, void *data_ref
		, int (*cmp)(), void (*free_fct)(void *))
{
	t_list	*index;
	t_list	*prev;
	t_list	*del;

	index = *begin_list;
	prev = 0;
	while (index)
	{
		if ((*cmp)(index->content, data_ref) != 0)
		{
			if (prev)
				prev->next = index->next;
			else
				*begin_list = index->next;
			del = index;
			index = index->next;
			(*free_fct)(del->content);
			free(del);
		}
		else
		{
			prev = index;
			index = index->next;
		}
	}
}

void	print_lst2(void	*data)
{
	t_wildcard	*s;

	s = (t_wildcard *)data;
	ft_printf("%s\n", s->prefix);
}
