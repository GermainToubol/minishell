/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:41:37 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/09 16:02:38 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "floran.h"

int	main(int ac, char **av, char **envp)
{
	t_list	*l_cmd;

	if (ac == 1)
		return (0);
	l_cmd = NULL;
	get_cmd(&av[1], envp, &l_cmd);
	ft_lstiter(l_cmd, print_node);
	ft_lstclear(&l_cmd, free_node);
	return (0);
}
