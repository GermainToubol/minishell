/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 01:01:16 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/07 22:12:46 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "utils.h"
#include "libft.h"

int	cpy_lst_wc_to_str(t_list **dest, t_list **src)
{
	t_list		*index;
	t_list		*new;
	t_wildcard	*wc;
	char		*tmp;

	index = *src;
	while (index)
	{
		wc = (t_wildcard *)index->content;
		tmp = ft_strdup(wc->prefix);
		if (tmp && ft_strchr(tmp, '\\'))
			clean_backslash(&tmp);
		if (!tmp)
			return (error_alloc(), 1);
		new = ft_lstnew(tmp);
		if (!new)
		{
			free(tmp);
			return (error_alloc(), 1);
		}
		ft_lstadd_back(dest, new);
		index = index->next;
	}
	return (0);
}

size_t	to_next_wc(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '*' && (i == 0 || s[i - 1] != '\\'))
			return (i + 1);
		i++;
	}
	return (0);
}

static int	get_prefix_path(char **path, char **prefix, char *to_add)
{
	if (to_add[0] == '/' && strjoin_custom(path, ft_strdup(("/"))))
		return (1);
	if (strjoin_custom(prefix, to_add))
		return (free(*path), 1);
	return (0);
}

t_wildcard	*get_wc_line(const char *cmd)
{
	char		*str[4];
	size_t		i;
	t_wildcard	*new;

	str[0] = NULL;
	str[1] = NULL;
	str[2] = NULL;
	i = to_next_wc(cmd);
	if (i == 0)
		return (NULL);
	i--;
	str[3] = ft_substr(cmd, 0, i);
	if (!str[3])
		return (error_alloc(), NULL);
	cmd = &cmd[i];
	if (get_prefix_path(&str[0], &str[1], str[3]))
		return (free(str[3]), NULL);
	if (strjoin_custom(&str[2], ft_strdup(cmd)))
		return (free(str[0]), free(str[1]), NULL);
	new = init_wc(str[0], str[1], str[2]);
	free(str[0]);
	free(str[1]);
	free(str[2]);
	return (new);
}
