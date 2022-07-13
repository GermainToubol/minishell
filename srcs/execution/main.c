/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:27:29 by gtoubol           #+#    #+#             */
/*   Updated: 2022/07/13 10:35:30 by fmauguin         ###   ########.fr       */
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

int	environment_init(t_list	**env_lst);

int	main(int argc, char **argv, char **env)
{
	t_list	*env_lst;
	int		i;
	char	**lines;

	(void)argv;
	env_lst = environment_copy(env);
	if (env_lst == NULL && env[0] != NULL)
		return (1);
	environment_update(env_lst);
	if (environment_init(&env_lst) != 0)
		return (1);
	if (argc == 1 && isatty(0))
		interactive_session(&env_lst);
	ft_lstclear(&env_lst, ft_freedico);
	return (get_status());
}

int	new_get_lvl(char *shlvl)
{
	int	new_lvl;

	new_lvl = 1 + ft_atoi(shlvl);
	if (new_lvl <= 0)
		return (0);
	if (new_lvl >= 1000)
	{
		ft_fprintf(2, "minishell: warning: shell level (%d) too high,"
			"resetting to 1\n", new_lvl);
		return (1);
	}
	return (new_lvl);
}

int	init_pwd(t_list **env_lst)
{
	char	buffer[6000];

	if (getcwd(buffer, 6000) == NULL)
	{
		perror("minishell: PWD");
		return (1);
	}
	if (environment_get(*env_lst, "PWD") == NULL
		&& environment_add(env_lst, "PWD") == NULL)
		return (ft_fprintf(2, "minishell: PWD: Initialisation Error"), 1);
	if (environment_set(*env_lst, "PWD", buffer) == -1)
		return (ft_fprintf(2, "minishell: PWD: Initialisation Error"), 1);
	return (0);
}

int	environment_init(t_list	**env_lst)
{
	char	*shlvl;
	int		ret;

	if (init_pwd(env_lst) == 1)
		return (ft_lstclear(env_lst, ft_freedico), 1);
	shlvl = environment_get(*env_lst, "SHLVL");
	if (shlvl == NULL)
	{
		if (environment_add(env_lst, "SHLVL=1") == NULL)
			return (1);
	}
	else
	{
		shlvl = ft_itoa(new_get_lvl(shlvl));
		if (shlvl == NULL)
		{
			ft_lstclear(env_lst, ft_freedico);
			return (1);
		}
		ret = environment_set(*env_lst, "SHLVL", shlvl);
		free(shlvl);
		if (ret < 0)
			return (ft_lstclear(env_lst, ft_freedico), 1);
	}
	return (0);
}
