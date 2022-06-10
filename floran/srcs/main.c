/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:41:37 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/10 14:15:13 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "floran.h"

int	main(int ac, char **av, char **envp)
{
	t_list	*l_cmd;
	char	**cmd_tab;
	char	*arg;
	int		signal;

	if (ac == 1)
		return (0);
	arg = arg_join(&av[1]);
	if (!arg)
		return (1);
	l_cmd = NULL;
	signal = check_line(arg);
	if (signal != 1)
		return (free(arg), signal);
	cmd_tab = split_sep(arg, "|");
	free(arg);
	if (!cmd_tab)
		return (1);
	get_cmd(cmd_tab, envp, &l_cmd);
	ft_lstiter(l_cmd, print_node);
	ft_lstclear(&l_cmd, free_node);
	return (0);
}
