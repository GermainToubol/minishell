/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_precision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:39:53 by gtoubol           #+#    #+#             */
/*   Updated: 2022/05/16 17:14:03 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "libft.h"

int	ft_printf_precision(const int fd, t_convert *convert)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (i < convert->precision)
	{
		n += write(fd, "0", 1);
		i++;
	}
	return (n);
}

int	ft_len_precision(int len, t_convert *convert)
{
	if (len > convert->precision)
		convert->precision = 0;
	else
		convert->precision -= len;
	return (convert->precision);
}

int	ft_atoi_precision(char *format, t_convert *convert)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (format[i] != '.')
		return (0);
	convert->has_precision = 1;
	convert->padd_char = ' ';
	i++;
	if (format[i] == '-')
	{
		convert->precision = -1;
		i++;
	}
	while (ft_isdigit(format[i]))
	{
		n = n * 10 + (format[i] - '0');
		i++;
	}
	if (convert->precision == -1)
		convert->precision = 1;
	else
		convert->precision = n;
	return (i);
}
