/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:34:19 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/20 02:32:28 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "utils.h"

int	main(int ac, char **av)
{
	char	*line;
	t_list	*lst;

	if (ac < 2)
		return (display_error("Error\nusage: ./wildcard [path]\n", 0), 1);
	ft_printf("\x1b[32mWelcome to wildcard\n\x1b[0m");
	line = ft_strdup(av[1]);
	lst = wildcards(line);
	if (!lst)
		return (1);
	ft_lstiter(lst, print_lst2);
	return (0);
}
