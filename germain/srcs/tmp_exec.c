/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 09:52:45 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/10 14:53:58 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

t_list	*tmp_init_exec(void)
{
	t_cmd	*tmp;
	int		i;
	t_list	*list;

	list = NULL;
	i = 0;
	while (i < 5)
	{
		tmp = (t_cmd *)malloc(sizeof(*tmp));
		tmp->inputs = NULL;
		tmp->outputs = NULL;
		tmp->path_exec = ft_strdup("/usr/bin/cat");
		tmp->cmd = ft_split("cat -e", ' ');
		ft_lstadd_back(&list, ft_lstnew(tmp));
		i++;
	}
	return (list);
}

void	tmp_free_cmd(void *content)
{
	t_cmd	*tmp;

	tmp = (t_cmd *)content;
	free(tmp->path_exec);
	ft_free_split(tmp->cmd);
	free(tmp);
}
