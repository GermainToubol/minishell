/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_init_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 10:59:03 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/10 14:55:31 by gtoubol          ###   ########.fr       */
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
				tmp = ft_lstnew(g_init_heredoc_pipe(command->inputs[i]->file,
							heredoc_list));
				ft_lstadd_back(&heredoc_list, tmp);
			}
			i++;
		}
		execline = execline->next;
	}
	return (heredoc_list);
}

static int	*g_init_heredoc_pipe(char *end_name, t_list *heredoc_list)
{
	int	*pipe_fds;

	pipe_fds = ft_calloc(2, sizeof(*pipe_fds));
	if (pipe_fds == NULL)
		return (NULL);
	if (pipe(pipe_fds) != 0)
	{
		free(pipe_fds);
		return (NULL);
	}
	g_put_heredoc_pipe(pipe_fds, end_name, heredoc_list);
	return (pipe_fds);
}

static int	g_put_heredoc_pipe(int *pipe_fds, char *end_name,
				t_list *heredoc_list)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid > 0)
	{
		wait(&status);
		return (0);
	}
	close(pipe_fds[0]);
	dup2(pipe_fds[1], STDOUT_FILENO);
	close(pipe_fds[1]);
	g_set_heredoc_content(end_name);
	g_clear_heredocs(&heredoc_list);
	exit(0);
}
