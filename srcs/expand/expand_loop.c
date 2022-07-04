/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 03:47:46 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/04 23:25:32 by fmauguin         ###   ########.fr       */
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

static int	do_basic(char *cmd, t_list **lst_tmp)
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

static int	do_basic_lst(const char *cmd, size_t *next, t_list **lst_tmp)
{
	char	*tmp;

	if (!lst_tmp)
		return (1);
	*next = to_next_index(cmd);
	tmp = ft_substr(cmd, 0, *next);
	ft_printf("tmp %s\nnext %i\n", tmp, *next);
	if (!tmp)
		return (display_error("Error allocation\n", 0), 1);
	return (do_basic(tmp, lst_tmp));
}

int	expand_quotes(const char *cmd, t_list **lst_tmp, size_t *next)
{
	char	*expand;

	*next = skip_quote(cmd);
	expand = quotes(cmd);
	if (!expand)
		return (1);
	if (!lst_tmp)
		return (1);
	if (do_basic(expand, lst_tmp))
		return (1);
	return (0);
}

int	expand_loop(const char *cmd, t_list **lst, t_list **lst_tmp)
{
	size_t	next;

	if (!*cmd)
		return (transfer_lst(lst, lst_tmp));
	else if (cmd[0] == '\'' || cmd[0] == '"')
	{
		if (expand_quotes(cmd, lst_tmp, &next))
			return (1);
	}
	else
	{
		if (do_basic_lst(cmd, &next, lst_tmp))
			return (1);
	}
	return (expand_loop(&cmd[next], lst, lst_tmp));
}