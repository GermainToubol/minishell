/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:14:08 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/03 12:53:02 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

long long	ft_atoll(char *s)
{
	long long	n;
	int			minus;

	minus = 1;
	n = 0;
	if (!s)
		return (0);
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			minus = -1;
		s++;
	}
	while (ft_isdigit(*s))
	{
		n *= 10;
		n += *s - '0';
		s++;
	}
	return (n * minus);
}
