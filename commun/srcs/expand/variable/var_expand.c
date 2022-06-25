/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 16:05:10 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/25 18:47:20 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "utils.h"

static int	get_var(const char *cmd, size_t *i, char **ret)
{
	char	*var;
	size_t	start;

	start = *i;
	if (ft_isdigit(cmd[*i]))
	{
		(*i)++;
		return (*ret = NULL, 0);
	}
	while (ft_isalnum(cmd[*i]) || cmd[*i] == '_')
		(*i)++;
	ft_printf("value: %s\n\n", *ret);
	var = ft_substr(cmd, start, *i - start);
	if (!var)
		return (display_error("Error allocation\n", 0), 1);
	ft_printf("\nget_var\nkey: %s\n", var);
	*ret = getenv(var);
	ft_printf("value: %s\n\n", *ret);
	free(var);
	if (!*ret)
		return (0);
	*ret = ft_strdup(*ret);
	if (!ret)
		return (display_error("Error allocation\n", 0), 1);
	return (0);
}

static int	strjoin_custom(char **dest, char *src)
{
	char	*tmp;

	if (!src)
		return (display_error("Error allocation\n", 0), 1);
	if (!*dest)
		*dest = src;
	else
	{
		tmp = ft_strjoin(*dest, src);
		free(src);
		if (!tmp)
			return (display_error("Error allocation\n", 0), 1);
		free(*dest);
		*dest = tmp;
	}
	return (0);
}

static int	rec_var(const char *cmd, size_t i, char **ret)
{
	size_t	start;
	char	*tmp;

	if (!cmd[i])
		return (0);
	ft_printf("\ncmd %s\n", &cmd[i]);
	start = i;
	while (cmd[i] && cmd[i] != '$')
		i++;
	ft_printf("cmd %s\n", &cmd[i]);
	if (i > start)
	{
		if (strjoin_custom(ret, ft_substr(cmd, start, i - start)))
			return (1);
		if (!cmd[i])
			return (0);
	}
	if (cmd[++i])
	{
		ft_printf("\nret: %s\n", *ret);
		if (get_var(cmd, &i, &tmp))
			return (1);
		if (tmp)
		{
			if (strjoin_custom(ret, tmp))
				return (1);
		}
		ft_printf("\nret: %s\n", *ret);
		ft_printf("\ncmd: %s\n", &cmd[i]);
		if (rec_var(cmd, i, ret))
			return (1);
	}
	return(0);
}

char	*expand_var(const char *cmd)
{
	char	*ret;

	if (!ft_strchr(cmd, '$'))
		return (display_error("no '$'\n", 0), NULL);
	ret = NULL;
	if (rec_var(cmd, 0, &ret))
	{
		if (ret)
			free(ret);
		return (NULL);
	}
	return (ret);
}
