/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:07:13 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/05 00:45:31 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <stdlib.h>
# include "parser.h"
# include "libft.h"

char		**do_expand(char **cmd);
char		**expand_loop_end(t_list **lst);
int			expand_loop(const char *cmd, t_list **lst, t_list **lst_tmp);

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

int 		expand_wc(const char *cmd, t_list **lst_tmp, size_t *next);
char		*quotes(const char *cmd);
size_t		to_next_index(const char *cmd);

#endif