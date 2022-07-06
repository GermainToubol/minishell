/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:17:45 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/07 00:58:36 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "libft.h"
#include "utils.h"

size_t	to_next_index(const char *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i] && cmd[i] != '"' && cmd[i] != '\''
		&& cmd[i] != '$')
		i++;
	return (i);
}

int	check_valid_wc(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '*' && (i == 0 || s[i - 1] != '\\'))
			return (1);
		i++;
	}
	return (0);
}

int	validate_lst(t_expand *expand)
{
	char	*save;

	if (!expand->tmp || !*expand->tmp)
		return (1);
	save = (char *)(*expand->tmp)->content;
	if (check_valid_wc(save))
	{
		if (expand_wc(save, expand))
			return (1);
	}
	if (ft_lstsize(*expand->tmp) == 1)
	{
		if (clean_backslash_expand(save, *expand->tmp))
			return (1);
	}
	else
		ft_list_remove_at(expand->tmp, 0, del_node_str);
	if (cat_lst(expand->saved, expand->tmp))
		return (1);
	ft_lstclear(expand->tmp, del_node_str);
	return (0);
}
