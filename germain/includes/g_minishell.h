/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_minishell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:07:25 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/17 14:51:39 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef G_MINISHELL_H
# define G_MINISHELL_H
# include <signal.h>
# include <unistd.h>
# include "libft.h"

# define PROMPT_NAME "MINISHELL$> "

typedef struct s_dictionnary
{
	char	*key;
	char	*value;
}	t_dico;

/* TMP */
t_list	*tmp_init_exec(void);
void	tmp_free_cmd(void *content);
void	ft_lstpop(t_list **lst, void (*del)(void *));
void	ft_lstsort(t_list **lst, int (*f)(void *, void *));

/* SESSION MANAGEMENT */
int		interactive_session(char **env);
int		non_interactive_session(char *arg, char **env);

/* ENVIRONMENT MANAGEMENT */
/** DICTIONNARY **/
t_dico	*ft_newdico(char *entry);
void	ft_freedico(void *dico);

/** ENVIRONMENT UTILITIES **/
t_list	*environment_copy(char **env);
t_list	*environment_add(t_list **old_env, char *var);
void	environment_remove(t_list **env, char *name);
int		environment_set(t_list *env, char *name, char *value);
char	*environment_get(t_list *env, char *name);
char	**environment_format(t_list *env);
int		environment_var_compare(void *content1, void *content2);

/* MEMORY MANAGEMENT */
int		local_memory_manager(void *ptr, int action, int flag);

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
int		builtin_cd(int argc, char **argv, t_list **env);
int		builtin_pwd(int argc, char **argv, t_list **env);
int		builtin_export(int argc, char **argv, t_list **env);

#endif
