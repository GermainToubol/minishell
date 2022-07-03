/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:07:13 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/04 00:36:10 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <stdlib.h>
# include "parser.h"

char		**do_expand(char **cmd);
char		**expand_loop_end(char ***new_cmd);
char		**expand_wc(char *cmd);
char		**do_basic(char *cmd);

void		free_tab3(char ***tab);

size_t		tab3_size(char ***new_cmd);

char		**expand_var(const char *cmd);
char		*expand_quotes(const char *cmd);
int			dup_hdoc(char **env, t_parse *parse);
int			close_hdoc(int fd, int fd_copy);

#endif