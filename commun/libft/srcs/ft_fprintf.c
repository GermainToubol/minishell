/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:40:13 by gtoubol           #+#    #+#             */
/*   Updated: 2022/05/16 16:52:27 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdarg.h>
#include "libft.h"

static int	put_print(const int fd, va_list args, t_convert *convert);
static int	normal_write(const int fd, int *i, char *fmt, int *valid);

int	ft_fprintf(const int fd, const char *format, ...)
{
	int			n;
	int			i;
	int			valid;
	va_list		args;
	t_convert	convert;

	n = 0;
	i = 0;
	valid = 1;
	va_start(args, format);
	while (format[i] != '\0')
	{
		if (format[i] != '%' || !valid)
		{
			n += normal_write(fd, &i, (char *)format + i, &valid);
			continue ;
		}
		valid = set_arguments((char *)format + i, &convert);
		if (!valid)
			continue ;
		i += valid;
		n += put_print(fd, args, &convert);
	}
	va_end(args);
	return (n);
}

static int	put_print(const int fd, va_list args, t_convert *convert)
{
	int	n;

	n = -1;
	if (convert->convertion == 'c')
		n = ft_printf_char(fd, (char)va_arg(args, int), convert);
	if (convert->convertion == 's')
		n = ft_printf_str(fd, va_arg(args, char *), convert);
	if (convert->convertion == 'p')
		n = ft_printf_ptr(fd, va_arg(args, void *), convert);
	if (convert->convertion == 'i' || convert->convertion == 'd')
		n = ft_printf_int(fd, va_arg(args, int), convert);
	if (convert->convertion == 'u')
		n = ft_printf_unsigned(fd, va_arg(args, unsigned int), convert);
	if (convert->convertion == 'x')
		n = ft_printf_hex(fd, va_arg(args, unsigned int), convert);
	if (convert->convertion == 'X')
		n = ft_printf_hex_caps(fd, va_arg(args, unsigned int), convert);
	if (convert->convertion == '%')
		n = ft_printf_percent(fd);
	return (n);
}

static int	normal_write(const int fd, int *i, char *fmt, int *valid)
{
	int	n;

	n = write(fd, fmt, 1);
	*i += 1;
	*valid = 1;
	return (n);
}
