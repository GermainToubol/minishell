/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:34:38 by gtoubol           #+#    #+#             */
/*   Updated: 2022/05/12 12:14:23 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stddef.h>
#include "libft.h"

int	ft_printf_ptr(const int fd, void *ptr, t_convert *convert)
{
	int	len;

	if (ptr == NULL)
	{
		len = 0;
		convert->padd_char = ' ';
		if (!convert->leftify)
			len += ft_printf_padding(fd, 5, convert);
		len += write(fd, "(nil)", 5);
		len += ft_printf_padding(fd, len, convert);
		return (len);
	}
	convert->alternate = '#';
	return (ft_printf_long_hex(fd, (unsigned long int)ptr,
			"0123456789abcdef0x",
			convert));
}
