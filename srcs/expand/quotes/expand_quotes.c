/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:46:09 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/07 00:52:48 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "libft.h"
#include "utils.h"

static char	*quotes(const char *cmd)
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

int	expand_quotes(t_expand *expand)
{
	char	*exp;
	size_t	next;

	next = skip_quote(&expand->line[expand->next]);
	exp = quotes(&expand->line[expand->next]);
	if (!exp)
		return (1);
	if (strjoin_custom(&expand->origin, ft_strdup(exp)))
		return (free(exp), 1);
	expand->next += next;
	return (do_basic(exp, expand->tmp));
}
