/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_hdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 23:56:07 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/30 01:51:15 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "lexer.h"

int	main(int ac, char **av)
{
	char	*file;
	char	*file2;

	if (ac <= 2)
		return (0);
	file = ft_strdup(av[1]);
	ft_printf("arg %s\n", file);
	if (set_hdoc(&file))
		return (1);
	file2 = ft_strdup(av[2]);
	if (set_hdoc(&file2))
		return (1);
	ft_printf("name %s\n", file);
	ft_printf("name %s\n", file2);
	unlink(file);
	unlink(file2);
	return (0);
}
