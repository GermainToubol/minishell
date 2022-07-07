/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_custom.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 01:00:43 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/07 22:12:46 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include <stdlib.h>

int	strjoin_custom(char **dest, char *src)
{
	char	*tmp;

	if (!src)
		return (error_alloc(), 1);
	if (!*dest)
		*dest = src;
	else
	{
		tmp = ft_strjoin(*dest, src);
		free(src);
		if (!tmp)
			return (error_alloc(), 1);
		free(*dest);
		*dest = tmp;
	}
	return (0);
}

int	strjoin_custom_lst(void **dest, char *src)
{
	char	*tmp;

	if (!src)
		return (error_alloc(), 1);
	if (!*dest)
		*dest = src;
	else
	{
		tmp = ft_strjoin((char *)(*dest), src);
		free(src);
		if (!tmp)
			return (error_alloc(), 1);
		free(*dest);
		*dest = tmp;
	}
	return (0);
}
