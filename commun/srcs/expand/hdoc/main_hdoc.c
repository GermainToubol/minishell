/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_hdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 23:56:07 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/30 00:13:24 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "lexer.h"

int	main(int ac, char **av)
{
	char	*file;
	char	*file2;

	if (ac == 1)
		return (0);
	file = ft_strdup(av[1]);
	if (get_hdoc(&file))
		return (1);
	file2 = ft_strdup(av[1]);
	if (get_hdoc(&file2))
		return (1);
	ft_printf("name %s\n", file);
	ft_printf("name %s\n", file2);
	return (0);
}
