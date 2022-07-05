/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:49:32 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/05 17:50:03 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	trim_ret(char *s, char **ret, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i + j])
	{
		(*ret)[i] = s[i + j];
		if (s[i + j] == c)
		{
			i++;
			while (s[i + j] == c)
				j++;
		}
		else
			i++;
	}
	(*ret)[i] = '\0';
}

char	*trim_c(char *s, char c)
{
	char	*ret;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i + j])
	{
		if (s[i + j] == c)
		{
			i++;
			while (s[i + j] == c)
				j++;
		}
		i++;
	}
	ret = ft_calloc(i + 1, sizeof(char));
	if (!ret)
		return (NULL);
	trim_ret(s, &ret, c);
	free(s);
	return (ret);
}
