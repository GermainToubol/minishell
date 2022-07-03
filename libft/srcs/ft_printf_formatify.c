/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_formatify.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:09:09 by gtoubol           #+#    #+#             */
/*   Updated: 2022/05/16 16:53:11 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	init_convert(t_convert *convert);
static void	set_format(char c, t_convert *convert);
static int	is_convertion(char c);

int	set_arguments(char *format, t_convert *convert)
{
	int	i;

	i = 1;
	init_convert(convert);
	while (format[i] && (format[i] == '#' || format[i] == '0'
			|| format[i] == '+' || format[i] == '-'
			|| format[i] == ' '))
	{
		set_format(format[i], convert);
		i++;
	}
	i += ft_atoi_padding(format + i, convert);
	i += ft_atoi_precision(format + i, convert);
	convert->convertion = format[i];
	if (!is_convertion(format[i]))
		return (0);
	i++;
	return (i);
}

static void	set_format(char fmt, t_convert *convert)
{
	if (fmt == '#')
		convert->alternate = '#';
	if (fmt == '0' && convert->leftify == 0)
		convert->padd_char = '0';
	if (fmt == '-')
	{
		convert->padd_char = ' ';
		convert->leftify = 1;
	}
	if (fmt == ' ' && !convert->sign)
		convert->sign = 1;
	if (fmt == '+')
		convert->sign = 2;
}

static void	init_convert(t_convert *convert)
{
	convert->convertion = 0;
	convert->alternate = 0;
	convert->padd_char = ' ';
	convert->leftify = 0;
	convert->padd_size = 0;
	convert->has_precision = 0;
	convert->precision = 1;
	convert->sign = 0;
}

static int	is_convertion(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'i' || c == 'd'
		|| c == 'u' || c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}
