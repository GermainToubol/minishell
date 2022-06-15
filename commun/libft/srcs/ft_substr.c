/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 18:06:12 by gtoubol           #+#    #+#             */
/*   Updated: 2022/05/12 14:31:29 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include "libft.h"

static size_t	the_min(size_t i, size_t j);

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	size;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		size = 1;
	else
		size = the_min(len, ft_strlen(s + start)) + 1;
	new = (char *)ft_calloc(size, sizeof(*new));
	if (!new)
		return (NULL);
	if (start > ft_strlen(s))
		new[0] = '\0';
	else
		ft_strlcpy(new, (char *)s + start, size);
	return (new);
}

static size_t	the_min(size_t i, size_t j)
{
	if (i < j)
		return (i);
	return (j);
}
