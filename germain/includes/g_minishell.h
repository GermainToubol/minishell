/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_minishell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:07:25 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/15 16:51:03 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef G_MINISHELL_H
# define G_MINISHELL_H
# include <signal.h>
# include <unistd.h>
# include "libft.h"

# define PROMPT_NAME "MINISHELL$> "

/* TMP */
t_list	*tmp_init_exec(void);
void	tmp_free_cmd(void *content);
void	ft_lstpop(t_list **lst, void (*del)(void *));

/* SESSION MANAGEMENT */
int		interactive_session(char **env);
int		non_interactive_session(char *arg, char **env);

/* ENVIRONMENT MANAGEMENT */
char	**environment_copy(char **env);
char	**environment_add(char **old_env, char *var);
char	**environment_remove(char **env, char *name);
char	*environment_get(char **env, char *name);
char	**environment_set(char **env, char *name, char *value);

/* MEMORY MANAGEMENT */
int	local_memory_manager(void *ptr, int action, int flag);

/* SIGNALS INTERACTIONS */
int		init_signal_interactive(struct sigaction *sa);
void	send_sig_list(void);
void	kill_from_lst(void *content);

/* EXECUTION */
void	run_line(char *line, char **env);
int		run_pipe_series(t_list *execline, char **env);
pid_t	exec_process(t_list *process, char **env, int *pipe_in, int *pipe_out);
int		wait_all(int n_process, pid_t last_pid);
void	clear_exec(t_list **execline, pid_t pid);

/* PIPE MANAGEMENT */
int		set_outpipe(t_list *execline, int *pipe_fds);

/* PID AND RELATED MEMORY */
void	extend_pid_list(pid_t pid);
void	free_pid_list(pid_t	pid);

/* BUILTIN */
int	builtin_cd(int argc, char **argv, char **env);

#endif
