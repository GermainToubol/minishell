/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_init_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 10:59:03 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/10 18:55:36 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

/*
  Le contenu des differents heredocs est contenu dans une liste de pipes.
 */

static int	*g_init_heredoc_pipe(char *end_name, t_list *heredoc_list);
static int	g_put_heredoc_pipe(int *pipe_fds, char *end_name,
				t_list *heredoc_list);

t_list	*g_init_heredocs(t_list *execline)
{
	t_list	*heredoc_list;
	t_list	*tmp;
	t_cmd	*command;
	int		i;

	heredoc_list = NULL;
	while (execline != NULL)
	{
		command = (t_cmd *)execline->content;
		i = 0;
		while (command->inputs != NULL && command->inputs[i] != NULL)
		{
			if (command->inputs[i]->heredoc == IS_HEREDOC)
			{
				ft_printf("heredoc /%s/>", command->inputs[i]->file);
				tmp = ft_lstnew(g_init_heredoc_document(command->inputs[i]->file,
							heredoc_list));
				ft_lstadd_back(&heredoc_list, tmp);
			}
			i++;
		}
		execline = execline->next;
	}
	return (heredoc_list);
}

static char	*g_init_heredoc_document(char *end_name, t_list *heredoc_list)
{
	char *filename;


}

static char *g_nbr_to_chr(int nbr)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_calloc(11, sizeof(*nbr));
	if (str == NULL)
		return (NULL);
	while (nbr != 0)
	{
		str[i] = nbr % 10  + '0';
		i++;
		nbr /= 10;
	}
	str[i] = 0;
}

static char *g_gene_heredoc_name(void)
{
	int		i;
	char	*name;
	char	*nbr;

	i = 0;
	while (i >= 0)
	{
		nbr = g_nbr_to_str(i);
		if (nbr == NULL)
			return (NULL);
		name = ft_strjoin("/tmp/.mns.", nbr);
		free(nbr);
		if (name == NULL)
	}
}
