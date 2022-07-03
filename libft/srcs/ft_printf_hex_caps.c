/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex_caps.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:04:49 by gtoubol           #+#    #+#             */
/*   Updated: 2022/05/16 17:09:51 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_printf_hex_caps(const int fd, unsigned int nbr, t_convert *convert)
{
	return (ft_printf_hex_base(fd, nbr, "0123456789ABCDEF0X", convert));
}
