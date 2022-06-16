/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freedico.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 10:15:02 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/16 10:19:31 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "minishell.h"
#include "g_minishell.h"

/**
   Free a dictionnary, considering all it elements have been alloced
   on the heap.

   @input: takes a `void *` pointer to be fully compatible with all
   the lst functions of the libft.
*/

void	ft_freedico(void *dico_ptr)
{
	t_dico	*dico;

	dico = (t_dico *)dico_ptr;
	free(dico->key);
	free(dico->value);
	free(dico);
}
