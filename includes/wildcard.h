/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 15:56:54 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/07 00:31:06 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include <stdlib.h>
# include <dirent.h>
# include "libft.h"

# define DIR_BUFFER 4096

typedef struct s_wildcard
{
	char	*prefix;
	char	*suffix;
	char	*dir_path;
	char	*found;
}	t_wildcard;

//display
void		print_node_wc(void	*data);
void		printf_wc(t_wildcard *mywc);

//Free
void		del_node_wc(void *data);

//prefix_suffix
t_wildcard	*get_wc_line(const char *cmd);
t_wildcard	*init_wc(char *path, char *prefix, char *suffix);
t_wildcard	*prefix_suffix(t_wildcard *mywc, char *found);
t_wildcard	*new_wc(t_wildcard *mywc, char *found, size_t i, size_t i2);
t_wildcard	*new_wc_path(t_wildcard *mywc, char *found, size_t i, size_t i2);
int			match_prefix(t_wildcard *mywc, char *found,
				size_t *i2);
int			check_found(t_wildcard *mywc, t_list **new_lst,
				char *dir_name);

//dir
char		*get_dir_name(t_wildcard *wc);
int			get_dir_match(t_wildcard *mywc, t_list **new_lst);

//core
int			rec_wildcards(t_list **lst, t_list **new_lst);
int			wildcards(t_wildcard	*mywc, t_list **ret);

//utils
t_wildcard	*cpy_wc(t_wildcard *wc);
int			cpy_lst_wc_to_str(t_list **dest, t_list **src);

#endif