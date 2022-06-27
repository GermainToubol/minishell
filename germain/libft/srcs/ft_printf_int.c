/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:26:49 by gtoubol           #+#    #+#             */
/*   Updated: 2022/05/16 17:13:09 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "libft.h"

static int	get_int_len(int n);
static void	printf_nbr(const int fd, int n);
static void	printf_sign(const int fd, int n, t_convert *convert);

int	ft_printf_int(const int fd, int n, t_convert *convert)
{
	int	len;

	len = get_int_len(n);
	len += ft_len_precision(len, convert);
	if ((convert->sign && n >= 0) || n < 0)
		len++;
	if (!convert->leftify)
	{
		if (convert->padd_char == '0')
			printf_sign(fd, n, convert);
		len += ft_printf_padding(fd, len, convert);
		if (convert->padd_char == ' ')
			printf_sign(fd, n, convert);
	}
	else
		printf_sign(fd, n, convert);
	ft_printf_precision(fd, convert);
	if (n != 0)
		printf_nbr(fd, n);
	len += ft_printf_padding(fd, len, convert);
	return (len);
}

static void	printf_sign(const int fd, int n, t_convert *convert)
{
	if (n < 0)
		ft_putchar_fd('-', fd);
	else
	{
		if (convert->sign == 1)
			ft_putchar_fd(' ', fd);
		if (convert->sign == 2)
			ft_putchar_fd('+', fd);
	}
}

static int	get_int_len(int n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	printf_nbr(const int fd, int n)
{
	int		sign;
	char	*digits;

	digits = "0123456789";
	sign = 1;
	if (n < 0)
		sign = -1;
	if (sign * n > 9 || sign * n < 0)
		printf_nbr(fd, sign * (n / 10));
	ft_putchar_fd(digits[sign * (n % 10)], fd);
}
