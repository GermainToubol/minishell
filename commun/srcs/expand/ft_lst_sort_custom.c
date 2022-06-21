/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_sort_custom.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:42:32 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/21 19:01:42 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wildcard.h"
#include "utils.h"

static int	ft_lst_sort_custom_loop(t_list *index, int (*cmp)())
{
	t_wildcard	*wc1;
	t_wildcard	*wc2;
	void		*s[2];
	int			ret;

	ret = 0;
	wc1 = (t_wildcard *)index->content;
	wc2 = (t_wildcard *)(index->next)->content;
	s[1] = ft_strjoin(wc1->dir_path, wc1->prefix);
	if (!s[1])
		return (display_error("Error allcation\n", 0), -1);
	s[2] = ft_strjoin(wc2->dir_path, wc2->prefix);
	if (!s[1])
	{
		free(s[1]);
		return (display_error("Error allcation\n", 0), -1);
	}
	if ((*cmp)(s[1], s[2]) > 0)
		ret = 1;
	free(s[1]);
	free(s[2]);
	return (ret);
}

void	ft_lst_sort_custom(t_list **begin_list, int (*cmp)())
{
	t_list	*index;
	void	*tmp;
	int		ret;

	index = *begin_list;
	if (!index)
		return ;
	while (index->next)
	{
		ret = ft_lst_sort_custom_loop(index, cmp);
		if (ret == -1)
			return ;
		else if (ret == 1)
		{
			tmp = index->content;
			index->content = (index->next)->content;
			(index->next)->content = tmp;
			index = *begin_list;
		}
		else
			index = index->next;
	}
}
