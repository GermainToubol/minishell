/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:46:09 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/06 15:11:05 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "libft.h"
#include "utils.h"

int	add_backslash(char **s)
{
	size_t	count;
	ssize_t	i;
	char	*ret;

	count = 0;
	i = -1;
	while ((*s)[++i])
		if ((*s)[i] == '*')
			count++;
	ret = ft_calloc(i + count + 1, sizeof(char));
	if (!ret)
		return (display_error("Error allocation\n", 0), 1);
	i = -1;
	count = 0;
	while ((*s)[++i])
	{
		if ((*s)[i] == '*')
			ret[i + count++] = '\\';
		ret[count + i] = (*s)[i];
	}
	ret[count + i] = '\0';
	free(*s);
	*s = ret;
	return (0);
}

char	*quotes(const char *cmd)
{
	char	*ret;
	char	*tmp;

	ret = NULL;
	tmp = ft_substr(cmd, 1, skip_quote(cmd) - 2);
	if (cmd[0] == '\'' && strjoin_custom(&ret, tmp))
		return (NULL);
	else if (cmd[0] == '"')
	{
		if (strjoin_custom(&ret, expand_var_quotes(tmp)))
			return (NULL);
	}
	ft_printf("ret %s\n", ret);
	if (add_backslash(&ret))
		return (free(ret), NULL);
	ft_printf("ret %s\n", ret);
	return (ret);
}
