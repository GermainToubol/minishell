/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_cleanable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 11:11:12 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/27 11:13:21 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "astree.h"
#include "parser.h"
#include "utils.h"
#include "g_minishell.h"
#include "minishell.h"

void	clear_cleanable(t_clean	*cleanable)
{
	astree_apply_suffix(cleanable->root, free_tree);
	free_parse_nohdoc(cleanable->parse);
	pid_clear_list();
	ft_lstclear(cleanable->env, ft_freedico);
}
