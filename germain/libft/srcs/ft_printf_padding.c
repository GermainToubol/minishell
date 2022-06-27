/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_padding.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:53:35 by gtoubol           #+#    #+#             */
/*   Updated: 2022/05/16 17:13:49 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "libft.h"

int	ft_atoi_padding(char *format, t_convert *convert)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (ft_isdigit(format[i]))
	{
		n = 10 * n + format[i] - '0';
		i++;
	}
	convert->padd_size = n;
	return (i);
}

int	ft_printf_padding(const int fd, int len, t_convert *convert)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (len + i < convert->padd_size)
	{
		n += write(fd, &(convert->padd_char), 1);
		i++;
	}
	convert->padd_size = 0;
	return (n);
}
