/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 03:47:46 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/05 19:46:44 by fmauguin         ###   ########.fr       */
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
		&& cmd[i] != '$' && cmd[i] != '*')
		i++;
	return (i);
}

int	do_basic(char *cmd, t_list **lst_tmp)
{
	t_list	*index;
	t_list	*new;

	index = *lst_tmp;
	ft_printf("do_basic\n");
	ft_printf("cmd %s\n", cmd);
	if (!index)
	{
		new = ft_lstnew(cmd);
		if (!new)
			return (display_error("Error allocation\n", 0), 1);
		ft_lstadd_back(lst_tmp, new);
		ft_printf("end_basic1\n");
		return (0);
	}
	while (index && !strjoin_custom_lst(&(index->content), ft_strdup(cmd)))
		index = index->next;
	free(cmd);
	if (index)
		return (1);
	ft_printf("end_basic2\n");
	return (0);
}

int	do_basic_lst(const char *cmd, t_list **lst_tmp, size_t *next)
{
	char	*tmp;

	if (!lst_tmp)
		return (1);
	*next = to_next_index(cmd);
	tmp = ft_substr(cmd, 0, *next);
	if (!tmp)
		return (display_error("Error allocation\n", 0), 1);
	return (do_basic(tmp, lst_tmp));
}

int	expand_quotes(const char *cmd, t_list **lst_tmp, size_t *next)
{
	char	*expand;

	ft_printf("cmd %s\n", cmd);
	*next = skip_quote(cmd);
	expand = quotes(cmd);
	ft_printf("\nexpand %s\ncmd %s\ncmdfull %s\n", expand, &cmd[*next], cmd);
	if (!expand)
		return (1);
	if (!lst_tmp)
		return (1);
	if (do_basic(expand, lst_tmp))
		return (1);
	ft_printf("q done\n");
	while (ft_strcmp(get_next_line(0), "\n")) {}
	return (0);
}

static int var_do_wc(t_list **lst_tmp, char *expand, const char *cmd, size_t *next)
{
	size_t	step;
	char	*tmp;

	if (ft_strchr(expand, '*'))
	{
		step = 0;
		if (strjoin_custom(&expand, ft_strdup(&cmd[*next])))
			return (free(expand), 1);
		if (expand_wc(expand, lst_tmp, &step))
			return (free(expand), 1);
		if (!*lst_tmp)
		{
			tmp = ft_substr(expand, 0, step + 1);
			ft_printf("expand %s\ntmp %s\n", expand, tmp);
			free(expand);
			if (!tmp)
				return (1);
			if (do_basic(tmp, lst_tmp))
				return (free(tmp), 1);
		}
		ft_printf("before step cmd %s\n", &cmd[*next]);
		*next += step - 1;
		ft_printf("after step cmd %s\n", &cmd[*next]);
	}
	else if (do_basic(expand, lst_tmp))
		return (1);
	return (0);
}

int	var_tab(char *expand, const char *cmd, t_list **lst, t_list **lst_tmp, size_t *next)
{
	char	**tmp2;
	size_t	tab_len;

	tmp2 = split_var(expand);
	if (!tmp2)
		return (1);
	tab_len = 0;
	while (tmp2[tab_len])
	{
		if (tmp2[tab_len + 1])
		{
			if (var_do_wc(lst_tmp, tmp2[tab_len], cmd, next))
				return (1);
			cat_lst(lst, lst_tmp);
			ft_printf("transfer done\n\n");
			ft_lstclear(lst_tmp, del_node_str);
		}
		else if (var_do_wc(lst_tmp, tmp2[tab_len], cmd, next))
			return (1);
		tab_len++;
	}
	free(tmp2);
	return (0);
}

int	expand_var(const char *cmd, t_list **lst, t_list **lst_tmp, size_t *next)
{
	char	*expand;

	if (!lst_tmp)
		return (1);
	*next = 1;
	if (get_var(cmd, next, &expand))
		return (1);
	if (expand && !ft_strchr(expand, ' '))
	{
		if (var_do_wc(lst_tmp, expand, cmd, next))
			return (1);
	}
	else if (expand && ft_strchr(expand, ' ') && var_tab(expand, cmd, lst, lst_tmp, next))
		return (1);
	return (0);
}



int	expand_loop(const char *cmd, t_list **lst, t_list **lst_tmp)
{
	size_t	next;
	if (!*cmd)
		return (cat_lst(lst, lst_tmp));
	else if (cmd[0] == '\'' || cmd[0] == '"')
	{
		if (expand_quotes(cmd, lst_tmp, &next))
			return (1);
	}
	else if (cmd[0] == '$')
	{
		if (expand_var(cmd, lst, lst_tmp, &next))
			return (1);
	}
	else if (cmd[0] == '*')
	{
		if (expand_wc(cmd, lst_tmp, &next))
			return (1);
	}
	else
	{
		if (do_basic_lst(cmd, lst_tmp, &next))
			return (1);
	}
	return (expand_loop(&cmd[next], lst, lst_tmp));
}