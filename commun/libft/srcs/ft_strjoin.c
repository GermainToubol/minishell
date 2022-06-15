/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 18:18:07 by gtoubol           #+#    #+#             */
/*   Updated: 2022/05/12 14:26:35 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*dest;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	dest = (char *)ft_calloc(len, sizeof(*dest));
	if (!dest)
		return (NULL);
	dest[0] = '\0';
	ft_strlcat(dest, s1, len);
	ft_strlcat(dest, s2, len);
	return (dest);
}
