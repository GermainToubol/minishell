/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_minishell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:07:25 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/23 18:05:06 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef G_MINISHELL_H
# define G_MINISHELL_H
# include <signal.h>
# include <unistd.h>
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
}	t_clean;

/* TMP */
t_list	*tmp_init_exec(void);
void	tmp_free_cmd(void *content);
void	ft_lstpop(t_list **lst, void (*del)(void *));
void	ft_lstsort(t_list **lst, int (*f)(void *, void *));
void	astree_apply_infix(t_astree *root, void (*f)(t_astree *));

/* SESSION MANAGEMENT */
int		interactive_session(t_list **env);
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
int		run_line(char *line, t_list **env);
int		run_pipe_series(t_parse **parse, t_list **env);
int		do_redirect(t_parse *parse);
int		do_bind_pipe(int *pfd);
int		get_exec_path(t_parse *parse, t_list **env);
pid_t	exec_process(t_parse *parse, t_list **env, int *pipe_in, int *pipe_out);
void	run_child(t_parse *parse, t_list **env, int *pipe_in, int *pipe_out);
void	run_parent(int *pipe_in);
int		run_builtin(t_parse *parse, t_list **env, int *pipe_in, int *pipe_out);
int		run_tree_exec(t_astree *root, t_parse **parse, t_list **env);
int		wait_all(int n_process, pid_t last_pid);

/* TREE EXEC */
pid_t	exec_tree(t_astree *node, int *pipe_in, int *pipe_out,
			t_clean *cleanable);
pid_t	exec_tree_and(t_astree *node, int *pipe_in, int *pipe_out,
			t_clean *cleanable);
pid_t	exec_tree_cmd(t_parse *parse, int *pipe_in, int *pipe_out,
			t_clean *cleanable);
pid_t	exec_tree_or(t_astree *node, int *pipe_in, int *pipe_out,
			t_clean *cleanable);
pid_t	exec_tree_pipe(t_astree *node, int *pipe_in, int *pipe_out,
			t_clean *cleanable);
int		count_wait_tree(t_astree *root);

/* PIPE MANAGEMENT */
int	set_outpipe(int *pipe_fds);

/* PID AND RELATED MEMORY */
void	extend_pid_list(pid_t pid);
void	free_pid_list(pid_t	pid);

/* BUILTIN */
int		builtin_cd(int argc, char **argv, t_list **env);
int		builtin_pwd(int argc, char **argv, t_list **env);
int		builtin_export(int argc, char **argv, t_list **env);
int		builtin_unset(int argc, char **argv, t_list **env);
int		builtin_env(int argc, char **argv, t_list **env);
int		builtin_echo(int argc, char **argv, t_list **env);
int		builtin_exit(void);
int		is_builtin(char *name);

#endif
