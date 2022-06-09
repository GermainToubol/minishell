/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_minishell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:07:51 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/09 15:34:59 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef G_MINISHELL_H
# define G_MINISHELL_H
/* for pid_t */
# include <unistd.h>

/* for t_list */
# include "libft.h"

/**
 * TMP PART: TO BE REMOVED
 *
 *
 ***************/

t_list	*tmp_init_exec(void);
void	tmp_free_cmd(void *content);

/* Ajouter a la libft */
void	ft_lstpop(t_list **lst, void (*del)(void *));

/**
***********************
 * END OF TMP
 *
 *
 */

pid_t	g_exec_process(t_list *process, char **env, int *pipe_in,
			int *pipe_out);
int		g_wait_all(int n_processes, pid_t last_process);
int		g_set_pipe(t_list *execline, int *pipe_fds);
#endif
