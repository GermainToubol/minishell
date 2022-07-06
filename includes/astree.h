/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:45:19 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/07 01:04:01 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTREE_H
# define ASTREE_H

# include "libft.h"
# include "parser.h"

typedef struct s_int_help
{
	int	i;
	int	min;
	int	max;
	int	is_open;
	int	is_done;
	int	depth;
}	t_int_help;

typedef struct s_astree
{
	t_parse			*cmd;
	int				depth;
	struct s_astree	*left;
	struct s_astree	*right;
}	t_astree;

//astree
int			create_astree(t_parse **parse, t_astree **root);
int			run_tree(t_astree *node, t_parse **parse, t_int_help *i);
int			get_next_right(t_parse **parse, t_int_help *i, int type);
int			get_next_left(t_parse **parse, t_int_help *i, int type);
t_int_help	*fill_t_int(t_parse **parse, int depth, int start, int type);
t_int_help	*new_right(t_parse **parse, t_int_help *i, int min);
t_astree	*create_node(t_parse *node, int depth);

//Display
void		print_cmd(t_astree *root);
void		display_tree(char *prefix, t_astree *node, int is_left);

//Free
void		free_tree(t_astree *root);

//Utils
void		astree_apply_suffix(t_astree *root, void (*f)(t_astree *));
#endif