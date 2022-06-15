/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:11:58 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/15 16:52:44 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strndup(char *src, size_t len)
{
	char	*r;
	size_t	i;

	if (!src)
		return (NULL);
	r = (char *)malloc((len + 1) * sizeof(char));
	if (!r)
		return (NULL);
	i = 0;
	while (src[i] && i < len)
	{
		r[i] = src[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}
