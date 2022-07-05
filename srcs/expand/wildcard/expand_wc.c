/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 03:33:06 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/05 23:59:14 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "expand.h"
#include "libft.h"
#include "utils.h"

static int	cpy_lst_wc_to_str(t_list **dest, t_list **src)
{
	t_list 		*index;
	t_list 		*new;
	t_wildcard	*wc;
	char		*tmp;

	if (!dest || !src)
		return (1);
	index = *src;
	while (index)
	{
		wc = (t_wildcard *)index->content;
		tmp = ft_strdup(wc->prefix);
		if (!tmp)
			return (display_error("Error allocation\n", 0), 1);
		new = ft_lstnew(tmp);
		if (!new)
		{
			free(tmp);
			return (display_error("Error allocation\n", 0), 1);
		}
		ft_lstadd_back(dest, new);
		index = index->next;
	}
	return (0);
}

static int	get_prefix_path(t_list *lst_tmp, char **path,
				char **prefix, char *to_add)
{
	char	*line;

	if (lst_tmp)
	{
		line = NULL;
		if (strjoin_custom(&line, ft_strdup((char *)lst_tmp->content)))
			return (free(to_add), 1);
		if (strjoin_custom(&line, to_add))
			return (free(line), 1);
		if (strjoin_custom(prefix, line))
			return (1);
		if (line[0] == '/' && strjoin_custom(path, ft_strdup("/")))
			return (free(prefix), 1);
		return (0);
	}
	if (strjoin_custom(prefix, to_add))
			return (1);
	if (to_add[0] == '/' && strjoin_custom(path, ft_strdup(("/"))))
		return (free(prefix), 1);
	return (0);
}

size_t	to_next_index_wc(const char *cmd)
{
	size_t	i;

	if (!cmd[0])
		return (0);
	i = 1;
	while (cmd[i] && cmd[i] != '"' && cmd[i] != '\''
		&& cmd[i] != '$')
		i++;
	return (i);
}

t_wildcard	*get_wc_line(const char *cmd, t_list *lst_tmp, size_t *next)
{
	char	*str[4];
	size_t	i;

	str[0] = NULL;
	str[1] = NULL;
	i = 0;
	while (cmd[i] && cmd[i] != '*')
		i++;
	str[3] = ft_substr(cmd, 0, i);
	if (!str[3])
		return (display_error("Error allocation\n", 0), NULL);
	cmd = &cmd[i];
	if (get_prefix_path(lst_tmp, &str[0], &str[1], str[3]))
		return (free(str[3]), NULL);
	*next = to_next_index_wc(cmd);
	str[2] = NULL;
	if (strjoin_custom(&str[2], ft_substr(cmd, 0, *next)))
		return (free(str[0]), free(str[1]), NULL);
	return (init_wc_2(str[0], str[1], str[2]));
}

t_wildcard	*get_wc_line_check(t_list *lst_tmp)
{
	char	*str[4];

	str[0] = NULL;
	str[1] = NULL;
	str[3] = ft_strdup("");
	if (!str[3])
		return (display_error("Error allocation\n", 0), NULL);
	if (get_prefix_path(lst_tmp, &str[0], &str[1], str[3]))
		return (free(str[3]), NULL);
	str[2] = ft_strdup("*");
	if (!str[2])
		return (free(str[0]), free(str[1]), NULL);
	return (init_wc_2(str[0], str[1], str[2]));
}

char	*str_get_parent(const char *s, const char *s2)
{
	ssize_t	i;
	char	*ret;

	if (!s | !s2)
		return (NULL);
	if (s2[0] == '/')
		return (ret = ft_strdup(s));
	i = ft_strlen(s);
	while (i-- > 0)
		if (s[i] == '/')
			break ;
	if (i >= 0 && s[i] != '/')
		ret = ft_strdup("");
	else
		ret = ft_substr(s, 0, i + 1);
	return (ret);
}

int	wc_found(t_list **lst_tmp, t_list **wc_lst)
{
	t_list	**lst;

	lst = ft_calloc(1, sizeof(t_list *));
	if (!lst)
		return (display_error("Error allocation\n", 0), 1);
	*lst = NULL;
	ft_lstiter(*wc_lst, print_lst2);
	if (cpy_lst_wc_to_str(lst, wc_lst))
	{
		free_lst_str(lst);
		return (1);
	}
	sort_list(lst);
	if (cat_lst(lst_tmp, lst))
		return (free_lst_str(lst), 1);
	free_lst_str(lst);
	return (0);
}

int	expand_wc_content(t_wildcard *wc, t_list **lst_tmp)
{
	t_list		**wc_lst;

	wc_lst = ft_calloc(1, sizeof(t_list *));
	if (!wc_lst)
		return (display_error("Error allcation\n", 0), -1);
	if (wildcards_wc(wc, wc_lst))
	{
		ft_lstclear(wc_lst, del_node_wc);
		return (free(wc_lst), -1);
	}
	if (*wc_lst)
	{
		ft_printf("\nMATCH\n");
		if (wc_found(lst_tmp, wc_lst))
			return (ft_lstclear(wc_lst, del_node_wc), free(wc_lst), -1);
		ft_lstclear(wc_lst, del_node_wc);
		free(wc_lst);
		return (1);
	}
	free(wc_lst);
	return (0);
}

int	validate_wc_content(t_wildcard *wc)
{
	t_list		**wc_lst;

	wc_lst = ft_calloc(1, sizeof(t_list *));
	if (!wc_lst)
		return (display_error("Error allcation\n", 0), -1);
	if (wildcards_wc(wc, wc_lst))
	{
		ft_lstclear(wc_lst, del_node_wc);
		return (free(wc_lst), -1);
	}
	if (*wc_lst)
	{
		ft_printf("\nMATCH\n");
		return (1);
	}
	ft_lstclear(wc_lst, del_node_wc);
	free(wc_lst);
	return (0);
}

int	validate_wc(t_expand *expand)
{
	t_list		*index;
	size_t		i;
	int			r;
	size_t		size;
	t_wildcard	*tmp;

	if (!expand || !expand->tmp)
		return (1);
	i = 0;
	index = *expand->tmp;
	size = ft_lstsize(index);
	while (index)
	{
		tmp = get_wc_line_check(index);
		i++;
		printf_wc(tmp);
		if (!tmp)
			return (1);
		r = validate_wc_content(tmp);
		if (r == -1)
			return (1);
		else if (r == 0)
		{
			ft_printf("\nNO match\n");
			index = index->next;
			ft_list_remove_at(expand->tmp, i - 1, del_node_str);
			i--;
			size--;
		}
		else
			index = index->next;
	}
	return (0);
}

int expand_wc(const char *cmd, t_expand *expand, size_t *next)
{
	t_wildcard	*tmp;
	t_list		*index;
	size_t		i;
	size_t		size;
	int			r;

	if (!expand->tmp || !cmd)
		return (1);
	if (cmd[0] && strjoin_custom(&expand->origin,
		ft_substr(cmd, 0, to_next_index_wc(cmd))))
		return (1);
	i = 0;
	index = *expand->tmp;
	if (!index)
	{
		*next = 0;
		expand->has_wc = 1;
		tmp = get_wc_line(cmd, index, next);
		printf_wc(tmp);
		if (!tmp)
			return (1);
		r = expand_wc_content(tmp, expand->tmp);
		if (r == -1)
			return (1);
		else if (r == 0)
		{
			if (no_match_lst(cmd, *next, expand))
				return (1);
			expand->has_wc = 0;
		}
		return (0);
	}
	size = ft_lstsize(*expand->tmp);
	while (i < size && index)
	{
		*next = 0;
		expand->has_wc = 1;
		i++;
		ft_printf("start\n");
		ft_printf("index %s\n", (char *)index->content);
		tmp = get_wc_line(cmd, index, next);
		printf_wc(tmp);
		if (!tmp)
			return (1);
		r = expand_wc_content(tmp, expand->tmp);
		if (r == -1)
			return (1);
		else if (r >= 0)
		{
			if (r == 0)
			{
				expand->has_wc = 0;
				ft_printf("\nNO match\n");
				if (no_match_lst(cmd, *next, expand))
					return (1);
			}
			index = index->next;
			ft_list_remove_at(expand->tmp, i - 1, del_node_str);
			i--;
			size--;
		}
		else
			index = index->next;
		ft_printf("\n\ni %i\nsize %i\n\n", i, size);
	}
	return (0);
}
