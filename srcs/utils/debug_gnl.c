/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_gnl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 22:26:29 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/06 23:45:15 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

void	debug_gnl(const char *s1, char *s2, int i)
{
	ft_printf("\n\nDebug============\n");
	if (s1)
		ft_printf("s1 : %s\n", s1);
	if (s2)
		ft_printf("s2 : %s\n", s2);
	if (i >= 0)
		ft_printf("i : %i\n", i);
	while (ft_strcmp("\n", get_next_line(0)))
	{
		ft_printf("Press enter...\n");
	}
	ft_printf("=================\n");
}
