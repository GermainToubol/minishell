/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 17:49:03 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/25 23:11:05 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expand.h"

int	main(int ac, char **av)
{
	char	*var;

	if (ac < 2)
		return (0);
	var = expand_var(av[1]);
	ft_printf("%s\n", var);
	free(var);
	return (0);
}
