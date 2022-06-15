/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:25:24 by gtoubol           #+#    #+#             */
/*   Updated: 2022/05/12 14:29:36 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include "libft.h"

static void	memmove_left(void *dest, const void *src, size_t n);
static void	memmove_right(void *dest, const void *src, size_t n);

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest == NULL && src == NULL)
		return (NULL);
	if ((long int)dest >= (long int)src)
		memmove_left(dest, src, n);
	else
		memmove_right(dest, src, n);
	return (dest);
}

static void	memmove_left(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*str_dest;
	char	*str_src;

	str_dest = (char *)dest;
	str_src = (char *)src;
	i = n;
	while (i > 0)
	{
		i--;
		str_dest[i] = str_src[i];
	}
}

static void	memmove_right(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*str_dest;
	char	*str_src;

	str_dest = (char *)dest;
	str_src = (char *)src;
	i = 0;
	while (i < n)
	{
		str_dest[i] = str_src[i];
		i++;
	}
}
