/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:14:08 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/03 17:13:38 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "utils.h"

int	ft_atoll(char *s, long long *n)
{
	int	minus;

	*n = 0;
	minus = 1;
	if (!s)
		return (1);
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			minus = -1;
		s++;
	}
	while (ft_isdigit(*s))
	{
		if (minus > 0 && (LLONG_MAX - *s + '0') / 10 < *n)
			return (1);
		if (minus < 0 && (LLONG_MIN + *s - '0') / 10 > -(*n))
			return (1);
		*n *= 10;
		*n += *s - '0';
		s++;
	}
	*n *= minus;
	return (0);
}
