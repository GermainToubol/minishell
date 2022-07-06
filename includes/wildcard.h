/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 15:56:54 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/06 19:17:34 by fmauguin         ###   ########.fr       */
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

int			strncmp_sep(char *s1, char *s2);
int			rec_wildcards(t_list **lst, t_list **new_lst);
int			update_wildcard(t_wildcard *mywc, char *line);
int			get_dir_match(t_wildcard *mywc, t_list **new_lst);
int			wildcards(char *line, t_list **ret);
int			check_found(t_wildcard *mywc, t_list **new_lst, char *dir_name);
int			wildcards_wc(t_wildcard	*mywc, t_list **ret);
int			match_prefix(t_wildcard *mywc, char *found,
				size_t *i2);
void		del_node_wc(void *data);
void		ft_list_remove_if(t_list **begin_list, void *data_ref,
				int (*cmp)(), void (*free_fct)(void *));
void		print_lst2(void	*data);
void		printf_wc(t_wildcard *mywc);
void		sort_list(t_list **lst);

char		*get_dir_name(t_wildcard *wc);

t_wildcard	*init_wc(char *line);
t_wildcard	*prefix_suffix(t_wildcard *mywc, char *found);
t_wildcard	*cpy_wc(t_wildcard *wc);
t_wildcard	*new_wc2(t_wildcard *mywc, char *found, char *tmp, size_t i);
t_wildcard	*new_wc(t_wildcard *mywc, char *found, size_t i, size_t i2);
t_wildcard	*new_wc_path2(t_wildcard *mywc, char *tmp, size_t i);
t_wildcard	*new_wc_path(t_wildcard *mywc, char *found, size_t i, size_t i2);

t_wildcard	*init_wc_2(char *path, char *prefix, char *suffix);

#endif