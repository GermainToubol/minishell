/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:07:20 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/10 17:09:46 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "floran.h"

long long	ft_atoll(char *str)
{
	long long	ret;
	int			minus;

	while ((*str <= 13 && *str >= 9) || *str == ' ')
		str++;
	ret = 0;
	minus = 1;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		minus = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		ret *= 10;
		ret += *str - '0';
		str++;
	}
	return (ret * minus);
}
