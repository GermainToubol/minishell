/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_minishell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:07:25 by gtoubol           #+#    #+#             */
/*   Updated: 2022/07/07 12:34:02 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef G_MINISHELL_H
# define G_MINISHELL_H
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include "parser.h"
# include "astree.h"

# define PROMPT_NAME "MINISHELL$> "

typedef struct s_dictionnary
{
	char	*key;
	char	*value;
}	t_dico;

typedef struct s_clean
{
	t_list		**env;
	t_astree	*root;
	t_parse		**parse;
	int			depth;
	int			pipe[1024];
	int			n_pipes;
}	t_clean;

/* TMP */
t_list		*tmp_init_exec(void);
void		tmp_free_cmd(void *content);
void		ft_lstpop(t_list **lst, void (*del)(void *));
void		ft_lstsort(t_list **lst, int (*f)(void *, void *));
void		astree_apply_infix(t_astree *root, void (*f)(t_astree *));
long long	ft_atoll_protected(char *s);
void		ft_tab_shift(char **tab, size_t n);
char		**ft_pathsplit(const char *str, char c);

/* SESSION MANAGEMENT */
int			interactive_session(t_list **env);
int			non_interactive_session(char *arg, char **env);

/* ENVIRONMENT MANAGEMENT */
/** DICTIONNARY **/
t_dico		*ft_newdico(char *entry);
void		ft_freedico(void *dico);

/** ENVIRONMENT UTILITIES **/
t_list		*environment_copy(char **env);
t_list		*environment_add(t_list **old_env, char *var);
void		environment_remove(t_list **env, char *name);
int			environment_set(t_list *env, char *name, char *value);
char		*environment_get(t_list *env, char *name);
char		**environment_format(t_list *env);
int			environment_var_compare(void *content1, void *content2);
void		environment_update(t_list *env);
t_list		*environment_call(void);

/* MEMORY MANAGEMENT */
int			local_memory_manager(void *ptr, int action, int flag);

/* SIGNALS INTERACTIONS */
int			init_signal_interactive(struct sigaction *sa);
void		send_sig_list(void);
void		kill_from_lst(void *content);
void		set_interupt(void);
void		reset_interupt(void);
int			is_interupted(void);
int			is_father(void);
void		unset_father(void);
void		reset_father(void);

/* EXECUTION */
int			run_line(char *line, t_list **env);
int			run_pipe_series(t_parse **parse, t_list **env);
int			do_redirect(t_parse *parse);
int			do_redirect_hdoc(char *filename, int target_fd);
int			redirect_name(t_redirect *redirect);
int			do_bind_pipe(int *pfd);
int			get_exec_path(t_parse *parse, t_list **env);
pid_t		exec_process(t_parse *parse, t_clean *cleanable,
				int *pipe_in, int *pipe_out);
void		run_child(t_parse *parse, t_list **env, int *pipe_in,
				int *pipe_out);
void		run_parent(int *pipe_in);
int			run_builtin(t_parse *parse, t_list **env, int *pipe_in,
				int *pipe_out);
int			run_tree_exec(t_astree *root, t_parse **parse, t_list **env);
int			wait_all(int n_process, pid_t last_pid);

/* TREE EXEC */
pid_t		exec_tree(t_astree *node, int *pipe_in, int *pipe_out,
				t_clean *cleanable);
pid_t		exec_tree_and(t_astree *node, int *pipe_in, int *pipe_out,
				t_clean *cleanable);
pid_t		exec_tree_cmd(t_parse *parse, int *pipe_in, int *pipe_out,
				t_clean *cleanable);
pid_t		exec_tree_or(t_astree *node, int *pipe_in, int *pipe_out,
				t_clean *cleanable);
pid_t		exec_tree_pipe(t_astree *node, int *pipe_in, int *pipe_out,
				t_clean *cleanable);
pid_t		exec_tree_add_level(t_astree *node, int *pipe_in, int *pipe_out,
				t_clean *cleanable);
int			count_wait_tree(t_astree *root, int depth);

/* CLEANABLE TOOLS */
void		cleanable_add_pipe(t_clean *cleanable, int *pipe_fds);
void		cleanable_pop_pipe(t_clean *cleanable);
void		cleanble_close_pipes(t_clean *cleanable);
void		clear_cleanable(t_clean *cleanable);

/* PIPE MANAGEMENT */
int			set_outpipe(int *pipe_fds);

/* STATUS MANAGEMENT */
void		set_status(int status);
int			get_status(void);
char		*get_status_str(void);

/* PID AND RELATED MEMORY */
int			manage_pid_list(pid_t pid, int action);
int			pid_extend_list(pid_t pid);
int			pid_signal_all(void);
int			pid_clear_list(void);
int			pid_remove_pid(pid_t pid);
pid_t		get_last_pid(void);
void		set_last_pid(pid_t pid);
int			pid_lstlen(void);
/* BUILTIN */
int			builtin_cd(int argc, char **argv, t_list **env);
int			builtin_pwd(int argc, char **argv, t_list **env);
int			builtin_export(int argc, char **argv, t_list **env);
int			builtin_unset(int argc, char **argv, t_list **env);
int			builtin_env(int argc, char **argv, t_list **env);
int			builtin_echo(int argc, char **argv, t_list **env);
int			builtin_exit(int argc, char **argv, t_list **env);
int			get_exit_state(void);
int			is_builtin(t_parse *parse);

#endif
