/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:49:38 by gtoubol           #+#    #+#             */
/*   Updated: 2022/07/07 09:57:16 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "expand.h"
#include "g_minishell.h"

size_t	ft_splitsize(char **strs)
{
	size_t	i;

	i = 0;
	if (strs == NULL)
		return (0);
	while (strs[i] != NULL)
		i++;
	return (i);
}

int	redirect_name(t_redirect *redirect)
{
	char	**lst;
	char	**new;

	lst = ft_calloc(2, sizeof(*lst));
	if (lst == NULL)
		return (ft_fprintf(2, "minishell: menory allocation error\n"),
			set_status(1), 1);
	lst[0] = redirect->file;
	new = do_expand(lst);
	if (new == NULL || ft_splitsize(new) != 1)
	{
		free(lst);
		ft_free_split(new);
		ft_fprintf(2, "minishell: %s: ambiguous redirect\n", redirect->file);
		return (set_status(1), 1);
	}
	else
	{
		ft_free_split(lst);
		redirect->file = new[0];
		free(new);
	}
	return (0);
}
