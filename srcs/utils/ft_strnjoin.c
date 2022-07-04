/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 22:56:00 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/04 15:54:54 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_strjoin_sep_content(char *ret, char *s1, char *s2, char sep)
{
	size_t	i;
	size_t	size1;
	size_t	size2;

	size1 = ft_strlen(s1);
	i = -1;
	while (++i < size1)
		ret[i] = s1[i];
	ret[i] = sep;
	size2 = ft_strlen(s2);
	i = -1;
	while (++i < size2)
		ret[i + size1 + 1] = s2[i];
	ret[i + size1 + 1] = '\0';
}

char	*ft_strjoin_sep(char *s1, char *s2, char sep)
{
	size_t	len;
	char	*ret;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (len > 0)
		len++;
	ret = ft_calloc(len + 1, sizeof(char));
	if (!ret)
		return (NULL);
	if (len == 0)
		ret[0] = '\0';
	else
		ft_strjoin_sep_content(ret, s1, s2, sep);
	return (ret);
}
