/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_update.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 02:30:59 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/04 02:31:00 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
#include "g_minishell.h"

static t_list	*_manage_environment(t_list *env, int action)
{
	static t_list	*env_save;

	if (action == 1)
		env_save = env;
	return (env_save);
}

void	environment_update(t_list *env)
{
	_manage_environment(env, 1);
}

t_list	*environment_call(void)
{
	return (_manage_environment(NULL, 0));
}
