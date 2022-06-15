/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:41:33 by gtoubol           #+#    #+#             */
/*   Updated: 2022/05/12 12:06:23 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "libft.h"

static int	get_len_unsigned(unsigned int nbr);
static void	putnbr_unsigned(const int fd, unsigned int nbr);

int	ft_printf_unsigned(const int fd, unsigned int nbr, t_convert *convert)
{
	int	len;

	len = get_len_unsigned(nbr);
	len += ft_len_precision(len, convert);
	if (!convert->leftify)
		len += ft_printf_padding(fd, len, convert);
	ft_printf_precision(fd, convert);
	if (nbr != 0)
		putnbr_unsigned(fd, nbr);
	len += ft_printf_padding(fd, len, convert);
	return (len);
}

static int	get_len_unsigned(unsigned int nbr)
{
	int	len;

	len = 0;
	while (nbr != 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

static void	putnbr_unsigned(const int fd, unsigned int nbr)
{
	char	*digits;

	digits = "0123456789";
	if (nbr > 9)
		putnbr_unsigned(fd, nbr / 10);
	ft_putchar_fd(digits[nbr % 10], fd);
}
