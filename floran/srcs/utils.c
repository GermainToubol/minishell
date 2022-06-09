/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:14:41 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/09 23:23:02 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "floran.h"

int	ft_iswhitspaces(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

char	*ft_join3(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*ret;

	if (!s1 || !s2 || !s3)
		return (NULL);
	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	ret = ft_strjoin(tmp, s3);
	free(tmp);
	return (ret);
}

char	*ft_strndup(char *src, int len)
{
	char	*r;
	int		i;

	r = (char *)malloc(len + 1 * sizeof(char));
	if (!r)
		return (NULL);
	i = -1;
	while (++i < len)
		r[i] = src[i];
	r[i] = '\0';
	return (r);
}

char	*arg_join(char **arg)
{
	int		i;
	char	*ret;
	char	*tmp;

	ret = (char *)malloc(sizeof(1));
	if (!ret)
		return (NULL);
	ret[0] = '\0';
	i = -1;
	while (arg[++i])
	{
		tmp = ft_join3(ret, " ", arg[i]);
		free(ret);
		if (!tmp)
			return (NULL);
		ret = ft_strdup(tmp);
		free(tmp);
		if (!ret)
			return (NULL);
	}
	return (ret);
}
