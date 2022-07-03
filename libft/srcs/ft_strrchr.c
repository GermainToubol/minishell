/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:54:05 by gtoubol           #+#    #+#             */
/*   Updated: 2022/05/09 09:47:48 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*previous;

	c = (char)c;
	i = 0;
	previous = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			previous = (char *)s + i;
		i++;
	}
	if (c == '\0')
		return ((char *)s + i);
	return (previous);
}
