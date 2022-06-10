/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 09:52:45 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/10 17:27:41 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

t_redirect **tmp_input(int i, char *filename);

t_list	*tmp_init_exec(void)
{
	t_cmd	*tmp;
	int		i;
	t_list	*list;

	list = NULL;
	i = 0;
	while (i < 17)
	{
		tmp = (t_cmd *)malloc(sizeof(*tmp));
		tmp->inputs = tmp_input(i, "FIN");
		tmp->outputs = NULL;
		tmp->path_exec = ft_strdup("/usr/bin/cat");
		tmp->cmd = ft_split("cat -e", ' ');
		ft_lstadd_back(&list, ft_lstnew(tmp));
		i++;
	}
	return (list);
}

t_redirect **tmp_input(int i, char *filename)
{
	t_redirect **inputs;

	if (i % 2 == 0)
		return (NULL);
	inputs = ft_calloc(3, sizeof(*inputs));
	inputs[2] = NULL;
	inputs[0] = ft_calloc(1, sizeof(**inputs));
	inputs[0]->file = ft_strdup(filename);
	inputs[0]->out = 0;
	inputs[0]->heredoc = IS_HEREDOC;
	inputs[0]->append = NO_APPEND;
	inputs[1] = ft_calloc(1, sizeof(**inputs));
	inputs[1]->file = ft_strdup(filename);
	inputs[1]->out = 0;
	if (i % 2 == 1)
		inputs[1]->heredoc = IS_HEREDOC;
	else
		inputs[1]->heredoc = NO_HEREDOC;
	inputs[1]->append = NO_APPEND;
	return (inputs);
}

void	tmp_free_cmd(void *content)
{
	t_cmd	*tmp;

	tmp = (t_cmd *)content;
	free(tmp->path_exec);
	ft_free_split(tmp->cmd);
	free(tmp);
}
