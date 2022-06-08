/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:05:51 by gtoubol           #+#    #+#             */
/*   Updated: 2022/05/09 09:45:36 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*src;
	unsigned char	target;

	i = 0;
	src = (unsigned char *)s;
	target = (unsigned char)c;
	while (i < n)
	{
		if (src[i] == target)
			return ((void *)(src + i));
		i++;
	}
	return (NULL);
}
