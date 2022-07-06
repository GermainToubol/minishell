/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 03:47:46 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/06 19:39:06 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "expand.h"
#include "libft.h"
#include "utils.h"

size_t	to_next_index(const char *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i] && cmd[i] != '"' && cmd[i] != '\''
		&& cmd[i] != '$')
		i++;
	return (i);
}

int	check_valid_wc(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '*' && (i == 0 || s[i - 1] != '\\'))
			return (1);
		i++;
	}
	return (0);
}

int	validate_lst(t_expand *expand)
{
	char	*save;

	if (!expand->tmp || !*expand->tmp)
		return (1);
	save = (char *)(*expand->tmp)->content;
	if (check_valid_wc(save))
	{
		if (expand_wc(save, expand))
			return (1);
	}
	if (ft_lstsize(*expand->tmp) == 1)
	{
		if (clean_backslash_expand(save, *expand->tmp))
			return (1);
	}
	else
		ft_list_remove_at(expand->tmp, 0, del_node_str);
	if (cat_lst(expand->saved, expand->tmp))
		return (1);
	ft_lstclear(expand->tmp, del_node_str);
	return (0);
}

int	do_basic(char *cmd, t_list **lst_tmp)
{
	t_list	*index;
	t_list	*new;

	index = *lst_tmp;
	if (!index)
	{
		new = ft_lstnew(cmd);
		if (!new)
			return (display_error("Error allocation\n", 0), 1);
		ft_lstadd_back(lst_tmp, new);
		return (0);
	}
	while (index && !strjoin_custom_lst(&(index->content), ft_strdup(cmd)))
		index = index->next;
	free(cmd);
	if (index)
		return (1);
	return (0);
}

int	do_basic_lst(t_expand *expand)
{
	char	*tmp;
	size_t	next;

	next = to_next_index(&expand->line[expand->next]);
	tmp = ft_substr(&expand->line[expand->next], 0, next);
	if (!tmp)
		return (display_error("Error allocation\n", 0), 1);
	if (strjoin_custom(&expand->origin, ft_strdup(tmp)))
		return (free(tmp), 1);
	expand->next += next;
	return (do_basic(tmp, expand->tmp));
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

int	var_tab(t_expand *expand, char *exp)
{
	char	**tmp2;
	size_t	tab_len;

	tmp2 = split_var(exp);
	if (!tmp2)
		return (1);
	tab_len = 0;
	print_tab(tmp2);
	while (tmp2[tab_len])
	{
		if (tmp2[tab_len + 1])
		{
			if (do_basic(tmp2[tab_len], expand->tmp))
				return (1);
			validate_lst(expand);
			ft_printf("transfer done\n\n");
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

	exp = NULL;
	expand->next++;
	if (get_var(expand->line, &expand->next, &exp))
		return (1);
	if (exp && !ft_strchr(exp, ' '))
	{
		if (do_basic(exp, expand->tmp))
			return (1);
	}
	else if (exp && ft_strchr(exp, ' ') && var_tab(expand, exp))
		return (1);
	return (0);
}

int	expand_loop(t_expand *expand)
{
//	debug_gnl(&expand->line[expand->next], expand->origin, (int)expand->next);
	if (!expand->line[expand->next])
		return (validate_lst(expand));
	else if (expand->line[expand->next] == '\''
		|| expand->line[expand->next] == '"')
	{
		if (expand_quotes(expand))
			return (1);
	}
	else if (expand->line[expand->next]== '$')
	{
		if (expand_var(expand))
			return (1);
	}
	else
	{
		if (do_basic_lst(expand))
			return (1);
	}
	return (expand_loop(expand));
}