/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:12:49 by gtoubol           #+#    #+#             */
/*   Updated: 2022/05/16 17:14:27 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stddef.h>
#include "libft.h"

static int	ft_strnlen(char *str, int n);
static int	size_print_null(t_convert *convert);

int	ft_printf_str(const int fd, char *str, t_convert *convert)
{
	int	len;
	int	size_to_print;

	convert->padd_char = ' ';
	if (str == NULL)
		size_to_print = size_print_null(convert);
	else if (convert->has_precision)
		size_to_print = ft_strnlen(str, convert->precision);
	else
		size_to_print = ft_strlen(str);
	len = 0;
	if (!convert->leftify)
		len += ft_printf_padding(fd, size_to_print, convert);
	if (str == NULL)
		len += write(fd, "(null)", size_to_print);
	else
		len += write(fd, str, size_to_print);
	len += ft_printf_padding(fd, len, convert);
	return (len);
}

static int	ft_strnlen(char *str, int n)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && i < n)
		i++;
	return (i);
}

static int	size_print_null(t_convert *convert)
{
	if (convert->has_precision && convert->precision < 6)
		return (0);
	return (6);
}
