/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree_apply_infix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 13:02:26 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/23 13:21:08 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "astree.h"
#include "minishell.h"
#include "g_minishell.h"

void	astree_apply_infix(t_astree *root, void (*f)(t_astree *))
{
	if (root->left)
		astree_apply_infix(root->left, f);
	f(root);
	if (root->right)
		astree_apply_infix(root->right, f);
}
