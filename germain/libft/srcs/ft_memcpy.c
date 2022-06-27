/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:40:29 by gtoubol           #+#    #+#             */
/*   Updated: 2022/05/12 14:29:25 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s_dest;
	unsigned char	*s_src;

	i = 0;
	s_dest = (unsigned char *)dest;
	s_src = (unsigned char *)src;
	if (s_dest != s_src)
	{
		while (i < n)
		{
			s_dest[i] = s_src[i];
			i++;
		}
	}
	return (dest);
}
