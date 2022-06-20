/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_interactive_session.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:43:20 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/14 13:04:11 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "minishell.h"
#include "g_minishell.h"

int	non_interactive_session(char *arg, char **env)
{
	(void)arg;
	(void)env;
	sleep(2);
	return (0);
}
