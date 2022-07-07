/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 16:05:10 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/07 15:42:29 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "expand.h"

static int	rec_var_q(const char *cmd, size_t i, char **ret);

char	*expand_var_quotes(const char *cmd)
{
	char	*ret;

	ret = NULL;
	if (!ft_strchr(cmd, '$'))
	{
		ret = ft_strdup(cmd);
		if (!ret)
			display_error("Error allocation\n", 0);
	}
	else if (rec_var_q(cmd, 0, &ret))
		return (free(ret), NULL);
	return (ret);
}

static int	rec_var_q(const char *cmd, size_t i, char **ret)
{
	size_t	start;
	char	*tmp;

	if (!cmd[i])
		return (0);
	start = i;
	while (cmd[i] && cmd[i] != '$')
		i++;
	if (i > start
		&& strjoin_custom(ret, ft_substr(cmd, start, i - start)))
		return (1);
	if (cmd[i] == '$')
	{
		i++;
		if (get_var(cmd, &i, &tmp))
			return (1);
		if (tmp && strjoin_custom(ret, tmp))
			return (1);
	}
	return (rec_var_q(cmd, i, ret));
}

static int	var_tab(t_expand *expand, char *exp)
{
	char	**tmp2;
	size_t	tab_len;

	tmp2 = split_var(exp);
	free(exp);
	if (!tmp2)
		return (1);
	tab_len = 0;
	while (tmp2[tab_len])
	{
		if (tmp2[tab_len + 1])
		{
			if (do_basic(tmp2[tab_len], expand->tmp))
				return (1);
			validate_lst(expand);
		}
		else if (do_basic(tmp2[tab_len], expand->tmp))
			return (1);
		tab_len++;
	}
	free(tmp2);
	return (0);
}


int	expand_var(t_expand *expand)
{
	char	*exp;
	char	*tmp;

	tmp = NULL;
	expand->next++;
	if (get_var(expand->line, &expand->next, &tmp))
		return (1);
	if (!tmp)
		return (0);
	exp = add_backslash_var(&tmp);
	if (!exp)
		return (free(tmp), 1);
	if (exp && !ft_strchr(exp, ' '))
	{
		if (do_basic(exp, expand->tmp))
			return (1);
	}
	else if (exp && ft_strchr(exp, ' ') && var_tab(expand, exp))
		return (1);
	return (0);
}
