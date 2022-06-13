/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:07:07 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/13 16:41:36 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "minishell.h"
#include "g_minishell.h"

/**
 * Main function of the basis running.
 * Check if the programm should be launch in an interactive session or not.
 *
 * @argc: if 1 start a new session. Otherwise try to execute the
 * command in the given files.
 *
 * @argv: list of the eventuel files.
 *
 * @env: environment parameter.
 *
 * If STDIN is a tty, start an interactive session.
 * If STDOUT is a tty show banner ?
 *
 */

int main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)env;
	if (argc != 1)
		return (0);
	if (isatty(0) == 1)
		interactive_session(env);
	else
		non_interactive_session(NULL, env);
	return (0);
}
