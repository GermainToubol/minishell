/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:45:19 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/25 01:34:40 by fmauguin         ###   ########.fr       */
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

void		astree_apply_suffix(t_astree *root, void (*f)(t_astree *));
void		print_cmd(t_astree *root);
void		free_tree(t_astree *root);
void		display_tree(char *prefix, t_astree *node, int is_left);

int			run_tree(t_astree *node, t_parse **parse, t_int_help *i);
int			create_astree(t_parse **parse, t_astree **root);

t_astree	*create_node(t_parse *node, int depth);

t_int_help	*fill_t_int(t_parse **parse, int depth, int start, int type);
t_int_help	*new_right(t_parse **parse, t_int_help *i, int min);
int			get_next_right(t_parse **parse, t_int_help *i, int type);
int			get_next_left(t_parse **parse, t_int_help *i, int type);
int			start_p(t_parse **parse, t_int_help *i);
#endif