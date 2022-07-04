/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:07:13 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/04 13:46:01 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <stdlib.h>
# include "parser.h"

char		**do_expand(char **cmd);
char		**expand_loop_end(char ***new_cmd);
char		**do_basic(char *cmd);

void		free_tab3(char ***tab);

size_t		tab3_size(char ***new_cmd);

char		*expand_quotes(const char *cmd);
//HDOC
int			dup_hdoc(char **env, t_parse *parse);
int			close_hdoc(int fd, int fd_copy);
int			read_hdoc(int hdoc_fd, int out_fd);
//VAR
int			var_expand_wc(char ***tab);
char		**split_var(const char *cmd);
size_t		skip_quote(const char *line);
int			get_var(const char *cmd, size_t *i, char **ret);
char		**expand_var(const char *cmd);
int			var_expand_wc(char ***tab);
char		*expand_var_quotes(const char *cmd);

char		**expand_wc(char *cmd);

#endif