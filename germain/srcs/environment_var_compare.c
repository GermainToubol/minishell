/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_var_compare.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:41:49 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/17 14:46:49 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

/**
   Compare the key related to the dictionnary in two contents.

   @return: positiv if first key is bigger, negative if smaller.
*/

int	environment_var_compare(void *content1, void *content2)
{
	t_dico	*d1;
	t_dico	*d2;

	d1 = (t_dico *)content1;
	d2 = (t_dico *)content2;
	return (ft_strcmp(d1->key, d2->key));
}
