/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:07:13 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/07 01:06:10 by fmauguin         ###   ########.fr       */
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
	char		*line;
	size_t		next;
}	t_expand;

//expand
char		**do_expand(char **cmd);
int			do_basic_lst(t_expand *expand);
int			expand_wc(char *cmd, t_expand *expand);
int			expand_quotes(t_expand *expand);
int			expand_var(t_expand *expand);

//core
int			expand_loop(t_expand *expand);
int			do_basic(char *cmd, t_list **lst_tmp);
int			validate_lst(t_expand *expand);

//HDOC
int			dup_hdoc(char **env, t_parse *parse);
int			close_hdoc(int fd, int fd_copy);
int			read_hdoc(int hdoc_fd, int out_fd);

//VAR
char		**split_var(const char *cmd);
int			get_var(const char *cmd, size_t *i, char **ret);
char		*expand_var_quotes(const char *cmd);

//utils
size_t		to_next_index(const char *cmd);
#endif