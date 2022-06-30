/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:53:29 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/27 12:57:23 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include "g_minishell.h"

static int	status_manager(int status, int action)
{
	static int	_status = 0;

	if (action == 1)
		_status = status & 0xff;
	return (_status);
}

void	set_status(int status)
{
	status_manager(status, 1);
}

int	get_status(void)
{
	return (status_manager(0, 0));
}

char	*get_status_str(void)
{
	static char	str[2] = {'0', '\0'};

	str[0] = get_status() + '0';
	return (ft_strdup(str));
}
