/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 11:21:34 by gtoubol           #+#    #+#             */
/*   Updated: 2022/05/03 11:59:04 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	itoa_fill_number(char *new, int div, int n);
static char	itoa_digit_to_char(unsigned int i);

char	*ft_itoa(int n)
{
	int		sign;
	int		len;
	int		div;
	char	*new;

	sign = 1;
	len = 10;
	div = 1000000000;
	if (n < 0)
		sign = -1;
	while (n / div == 0 && div > 1)
	{
		div /= 10;
		len --;
	}
	if (sign == 1)
		new = (char *)ft_calloc(len + 1, sizeof(*new));
	else
		new = (char *)ft_calloc(len + 2, sizeof(*new));
	if (new == NULL)
		return (NULL);
	itoa_fill_number(new, div, n);
	return (new);
}

static void	itoa_fill_number(char *new, int div, int n)
{
	int	i;
	int	sign;

	sign = 1;
	i = 0;
	if (n < 0)
	{
		sign = -1;
		new[0] = '-';
		i = 1;
	}
	while (div > 1)
	{
		new[i] = itoa_digit_to_char(sign * (n / div));
		n = n % div;
		div /= 10;
		i++;
	}
	new[i] = itoa_digit_to_char(sign * (n % 10));
	new[i + 1] = '\0';
}

static char	itoa_digit_to_char(unsigned int i)
{
	char	*digits;

	digits = "0123456789";
	return (digits[i % 10]);
}
