/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 09:48:12 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/09 17:32:28 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_list	*execline;

	(void)argc;
	(void)argv;
	execline = tmp_init_exec();
	return (g_run_pipe_series(execline, env));
}
