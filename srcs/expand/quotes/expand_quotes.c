/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:46:09 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/07 14:13:07 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "libft.h"
#include "utils.h"

static char	*quotes(const char *cmd)
{
	char	*ret;
	char	*tmp;

	tmp = NULL;
	ret = ft_substr(cmd, 1, skip_quote(cmd) - 2);
	if (cmd[0] == '\'' && strjoin_custom(&ret, ret))
		return (NULL);
	else if (cmd[0] == '"')
	{
		if (strjoin_custom(&tmp, expand_var_quotes(ret)))
			return (NULL);
	}
	ret = add_backslash(tmp);
	free(tmp);
	if (!ret)
		return (NULL);
	return (ret);
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
