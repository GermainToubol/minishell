/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:46:09 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/07 23:06:41 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "libft.h"
#include "utils.h"

static char	*quotes_content(const char *cmd, char *src)
{
	char	*ret;
	char	*empty;

	ret = NULL;
	if (cmd[0] == '\'')
	{
		ret = ft_strdup(src);
		if (!ret)
			return (error_alloc(), NULL);
	}
	else if (cmd[0] == '"')
	{
		if (expand_var_quotes(src, &ret))
			return (NULL);
		if (!ret)
		{
			empty = ft_strdup("");
			if (!empty)
				return (error_alloc(), NULL);
			return (empty);
		}
	}
	return (ret);
}

static char	*quotes(const char *cmd)
{
	char	*ret;
	char	*tmp;

	ret = ft_substr(cmd, 1, skip_quote(cmd) - 2);
	if (!ret)
		return (error_alloc(), NULL);
	tmp = quotes_content(cmd, ret);
	free(ret);
	if (!tmp)
		return (NULL);
	if (ft_strchr(tmp, '*'))
	{
		ret = add_backslash(tmp);
		free(tmp);
		return (ret);
	}
	return (tmp);
}

int	expand_quotes(t_expand *expand)
{
	char	*exp;
	size_t	next;

	next = skip_quote(&expand->line[expand->next]);
	exp = quotes(&expand->line[expand->next]);
	if (!exp)
		return (1);
	expand->next += next;
	return (do_basic(exp, expand->tmp));
}
