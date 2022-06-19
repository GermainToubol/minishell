/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 15:56:54 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/20 00:13:39 by fmauguin         ###   ########.fr       */
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
}	t_wildcard;

t_list	*wildcards(char *line);
int		strncmp_sep(char *s1, char *s2);
void	del_node(void *data);
void	ft_list_remove_if(t_list **begin_list, void *data_ref
		, int (*cmp)(), void (*free_fct)(void *));
void	print_lst2(void	*data);
void	printf_wc(t_wildcard *mywc);

#endif