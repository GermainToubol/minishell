/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:03:13 by gtoubol           #+#    #+#             */
/*   Updated: 2022/05/16 16:54:02 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_printf_hex(const int fd, unsigned int nbr, t_convert *convert)
{
	return (ft_printf_hex_base(fd, nbr, "0123456789abcdef0x", convert));
}
