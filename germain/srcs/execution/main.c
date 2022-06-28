/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:27:29 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/28 14:15:53 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

/**
   First entry of the program:
   - Creation of the environment list.
*/

int	environment_init(t_list	**env_lst);

int	main(int argc, char **argv, char **env)
{
	t_list	*env_lst;

	(void)argv;
	env_lst = environment_copy(env);
	if (env_lst == NULL && env[0] != NULL)
		return (1);
	if (environment_init(&env_lst) != 0)
		return (1);
	if (argc == 1 && isatty(0))
		interactive_session(&env_lst);
	if (argc == 3)
		run_line(ft_strdup(argv[2]), &env_lst);
	ft_lstclear(&env_lst, ft_freedico);
	return (0);
}

int	environment_init(t_list	**env_lst)
{
	char	*shlvl;

	shlvl = environment_get(*env_lst, "SHLVL");
	if (shlvl == NULL)
		environment_add(env_lst, "SHLVL=1");
	else
	{
		shlvl = ft_itoa(1 + ft_atoi(shlvl));
		if (shlvl == NULL)
		{
			ft_lstclear(env_lst, ft_freedico);
			return (1);
		}
		environment_set(*env_lst, "SHLVL", shlvl);
		free(shlvl);
	}
	return (0);
}
