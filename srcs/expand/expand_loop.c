/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 03:47:46 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/04 22:32:57 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "expand.h"
#include "libft.h"
#include "utils.h"


static int	transfer_lst(t_list **dest, t_list **src)
{
	t_list *index;

	if (!dest || !src)
		return (1);
	index = *src;
	while (index)
	{
		ft_lstadd_back(dest, index);
		index = index->next;
	}
	*src = NULL;
	return (0);
}

size_t	to_next_index(const char *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i]
		&& (cmd[i] != '"' || cmd[i] != '\'' || cmd[i] != '$'))
		i++;
	return (i);
}

static int	do_basic_lst(const char *cmd, size_t end, t_list **lst_tmp)
{
	char	*tmp;
	t_list	*index;
	t_list	*new;

	if (!lst_tmp)
		return (1);
	tmp = ft_substr(cmd, 0, end);
	if (!tmp)
		return (display_error("Error allocation\n", 0), 1);
	index = *lst_tmp;
	if (!index)
	{
		new = ft_lstnew(tmp);
		if (!new)
			return (display_error("Error allocation\n", 0), 1);
		ft_lstadd_back(lst_tmp, new);
		return (0);
	}
	while (index && !strjoin_custom(index->content, ft_strdup(tmp)))
		index = index->next;
	free(tmp);
	if (index)
		return (1);
	return (0);
}

int	expand_loop(const char *cmd, t_list **lst, t_list **lst_tmp)
{
	size_t	next;

	if (!*cmd)
		return (transfer_lst(lst, lst_tmp));
	else
	{
		ft_printf("cmd %s\n", cmd);
		next = to_next_index(cmd);
		if (do_basic_lst(cmd, next, lst_tmp))
			return (1);
		return (expand_loop(&cmd[next], lst, lst_tmp));
	}
}