/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_in_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:04:51 by gtoubol           #+#    #+#             */
/*   Updated: 2022/07/04 21:50:14 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	split_get_words(char const *s, char c, t_list **lst);

int		ft_split_in_lst(char const *s, char c, t_list **lst)
{
	if (!s)
		return (1);
	split_get_words(s, c, lst);
	return (0);
}

static void	split_get_words(char const *s, char c, t_list **lst)
{
	char	*str;
	int		i;
	int		j;
	t_list	*new;

	i = 0;
	while (s[i] != 0)
	{
		j = 0;
		while (s[i + j] && s[i + j] != c)
			j++;
		if (j != 0)
		{
			str = ft_substr(s, i, j);
			if (!str)
				return ;
			new = ft_lstnew(str);
			if (!new)
				return (free(str));
			ft_lstadd_back(lst, new);
			i += j;
		}
		else
			i++;
	}
}
