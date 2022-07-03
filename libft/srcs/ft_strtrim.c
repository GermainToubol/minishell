/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 09:38:30 by gtoubol           #+#    #+#             */
/*   Updated: 2022/05/06 13:04:46 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	trim_get_start(char const *s1, char const *set);
static int	trim_get_end(char const *s1, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		len;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_substr(s1, 0, ft_strlen(s1) + 1));
	start = trim_get_start(s1, set);
	end = trim_get_end(s1, set);
	if (end - start >= 0)
		len = end - start + 1;
	else
		len = 0;
	return (ft_substr(s1, start, (unsigned int)len));
}

static int	trim_get_start(char const *s1, char const *set)
{
	int	start;

	start = 0;
	while (s1[start] != '\0' && ft_strchr(set, s1[start]) != NULL)
		start++;
	return (start);
}

static int	trim_get_end(char const *s1, char const *set)
{
	int	end;

	end = ft_strlen(s1);
	while (end >= 0 && ft_strchr(set, s1[end]))
		end--;
	return (end);
}
