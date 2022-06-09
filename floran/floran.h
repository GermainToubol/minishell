/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floran.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:08:39 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/09 23:29:46 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLORAN_H
# define FLORAN_H

# include "minishell.h"
# include "libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# define L_PATH 5
# define EXIT 1
# define NO_EXIT 0

//parse
int			get_cmd(char **av, char **envp, t_list **l_cmd);
char		*arg_join(char **arg);
t_redirect	**split_red(char *str, char *sep);
t_cmd		*fill_cmd_strct(char **path, char *cmd);
t_redirect	*fill_redirect(char *str, char *sep, char *out);
char		*check_path(char **path, char *cmd);
int			is_sep(char c, char *sep);

//free
void		free_node(void *data);
void		free_tab(char **tab);
void		free_red(t_redirect **tab);

//utils
char		*ft_join3(char *s1, char *s2, char *s3);
char		*ft_strndup(char *src, int len);
char		**split_sep(char *str, char *sep, int limit);
int			ft_iswhitspaces(char c);

//Error
void		error_msg(char *err, int do_exit, int signal);

//debug
void		print_node(void *data);

#endif