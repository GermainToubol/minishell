/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 17:49:03 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/26 17:53:13 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expand.h"

int	main(int ac, char **av)
{
	char	*var;

	if (ac < 2)
		return (0);
	var = NULL;
	ft_printf("arg %s\n\n", av[1]);
	if (ft_strchr(av[1], '\'') || ft_strchr(av[1], '"'))
		var = expand_quotes(av[1]);
	else if (ft_strchr(av[1], '$'))
		var = expand_var(av[1]);
	ft_printf("\nmain: %s\n", var);
	free(var);
	return (0);
}
