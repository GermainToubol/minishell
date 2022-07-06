/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:07:13 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/06 16:39:10 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <stdlib.h>
# include "parser.h"
# include "libft.h"

typedef struct s_expand
{
	t_list		**saved;
	t_list		**tmp;
	int			has_wc;
	char		*line;
	char		*origin;
	size_t		fixed;
	size_t		next;
}	t_expand;

char		**do_expand(char **cmd);
char		**expand_loop_end(t_list **lst);
int			expand_loop(t_expand *expand);
int			do_basic(char *cmd, t_list **lst_tmp);
int			do_basic_lst(t_expand *expand);
int			no_match_lst(const char *line, size_t size, t_expand *expand);
int			validate_wc(t_expand *expand);

void		free_tab3(char ***tab);

size_t		tab3_size(char ***new_cmd);

//HDOC
int			dup_hdoc(char **env, t_parse *parse);
int			close_hdoc(int fd, int fd_copy);
int			read_hdoc(int hdoc_fd, int out_fd);
//VAR
int			var_expand_wc(char ***tab);
char		**split_var(const char *cmd);
size_t		skip_quote(const char *line);
int			get_var(const char *cmd, size_t *i, char **ret);
char		**var_expand(const char *cmd);
int			var_expand_wc(char ***tab);
char		*expand_var_quotes(const char *cmd);

int 		expand_wc(char *cmd, t_expand *expand);
char		*quotes(const char *cmd);
size_t		to_next_index(const char *cmd);
int			clean_backslash(char **s);
int			add_backslash(char **s);

#endif