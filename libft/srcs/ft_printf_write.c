/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_write.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 11:09:32 by gtoubol           #+#    #+#             */
/*   Updated: 2022/07/04 11:09:33 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "libft.h"

static int	printf_clear_buffer(int fd, char *to_print, int *n_char)
{
	if (write(fd, to_print, *n_char) < 0)
	{
		*n_char = 0;
		return (-1);
	}
	*n_char = 0;
	to_print[0] = 0;
	return (0);
}

int	ft_printf_write(int fd, char *str, int n)
{
	static char	to_print[PRINT_BUFFER_SIZE];
	static int	n_char = 0;
	int			i;

	if (str == NULL && n == -1)
	{
		if (printf_clear_buffer(fd, to_print, &n_char) < 0)
			return (-1);
		return (0);
	}
	i = 0;
	while (i < n)
	{
		if (n_char < PRINT_BUFFER_SIZE)
		{
			to_print[n_char] = str[i];
			n_char++;
			i++;
			continue ;
		}
		if (printf_clear_buffer(fd, to_print, &n_char) < 0)
			return (-1);
	}
	return (n);
}
