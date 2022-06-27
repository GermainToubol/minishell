/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 11:49:39 by gtoubol           #+#    #+#             */
/*   Updated: 2022/05/03 11:58:01 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		sign;
	char	*digits;

	digits = "0123456789";
	sign = 1;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		sign = -1;
	}
	if (sign * n >= 10 || sign * n < 0)
		ft_putnbr_fd(sign * (n / 10), fd);
	ft_putchar_fd(digits[sign * (n % 10)], fd);
}
