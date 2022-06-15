/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:49:55 by gtoubol           #+#    #+#             */
/*   Updated: 2022/05/12 14:21:52 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	len;
	char	*new;

	len = ft_strlen(str);
	new = (char *)ft_calloc(len + 1, sizeof(*new));
	if (!new)
		return (NULL);
	ft_strlcpy(new, str, len + 1);
	return (new);
}
