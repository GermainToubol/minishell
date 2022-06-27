/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:27:29 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/27 16:36:55 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

/**
   First entry of the program:
   - Creation of the environment list.
*/

int	main(int argc, char **argv, char **env)
{
	t_list	*env_lst;

	(void)argc;
	(void)argv;
	env_lst = environment_copy(env);
	if (env_lst == NULL && env[0] != NULL)
		return (1);
	if (argc == 1 && isatty(0))
		interactive_session(&env_lst);
	ft_lstclear(&env_lst, ft_freedico);
	return (0);
}

int	environment_init(t_list	*env_lst)
{
	char	shvlvl;

	shlvl = environment_get("SHLVL");
	if (shlvl == NULL)
}
