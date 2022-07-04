/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_father.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 02:42:31 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/04 02:42:46 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "g_minishell.h"

static int	_fatherness(int action)
{
	static int	_is_father = 1;

	if (action == 0)
		_is_father = 0;
	if (action == -1)
		_is_father = 1;
	return (_is_father);
}

int	is_father(void)
{
	return (_fatherness(1));
}

void	unset_father(void)
{
	_fatherness(0);
}

void	reset_father(void)
{
	_fatherness(-1);
}
