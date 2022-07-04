/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 22:56:00 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/04 02:52:33 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_strnjoin_content(char *ret, char **tab, char sep)
{
	size_t	i;
	size_t	j;
	size_t	size;

	size = 0;
	i = -1;
	while (tab[++i])
	{
		j = -1;
		while (tab[i][++j])
		{
			ret[size++] = tab[i][j];
		}
		if (tab[i + 1])
			ret[size++] = sep;
	}
	ret[size++] = '\0';
}

char	*ft_strnjoin(char **tab, char sep)
{
	size_t	count;
	size_t	len;
	char	*ret;

	count = -1;
	len = 0;
	if (!tab)
		return (NULL);
	while (tab[++count])
		len += ft_strlen(tab[count]);
	len += count - 1;
	if (len == 0)
		return (NULL);
	ret = ft_calloc(len + 1, sizeof(char));
	if (!ret)
		return (NULL);
	ft_strnjoin_content(ret, tab, sep);
	return (ret);
}
