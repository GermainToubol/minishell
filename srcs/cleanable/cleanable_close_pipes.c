/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanable_close_pipes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 02:42:16 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/04 02:42:17 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "g_minishell.h"
#include "minishell.h"

void	cleanble_close_pipes(t_clean *cleanable)
{
	while (cleanable->n_pipes > 0)
		cleanable_pop_pipe(cleanable);
}
