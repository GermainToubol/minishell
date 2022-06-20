/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 15:56:41 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/20 02:17:58 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "utils.h"
#include <unistd.h>

int	update_wildcard(t_wildcard *mywc, char *line)
{
	size_t	i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (line[i] && line[i] != '*')
		i++;
	tmp2 = ft_substr(line, 0, i);
	tmp = ft_strjoin(mywc->prefix, tmp2);
	free(tmp2);
	free(mywc->prefix);
	mywc->prefix = ft_strdup(tmp);
	free(tmp);
	if (line[i])
	{
		while (line[i] == '*')
			i++;
		free(mywc->suffix);
		if (!line[i])
			i--;
		mywc->suffix = ft_strdup(&line[i]);
	}
	return (0);
}

int	get_match_indir(t_list *old_lst, t_list **new_lst)
{
	struct dirent	*dir;
	DIR				*d;
	t_wildcard		*new;
	t_wildcard		*mywc;

	mywc = (t_wildcard *)old_lst->content;
	d = opendir(mywc->dir_path);
	if (!d)
		return (1);
	while (1)
	{
		dir = readdir(d);
		if (!dir)
			break ;
		if (!ft_strncmp(mywc->prefix, dir->d_name, ft_strlen(mywc->prefix)))
		{
			new = prefix_suffix(mywc, dir->d_name);
			if (new)
				ft_lstadd_back(new_lst, ft_lstnew(new));
		}
	}
	closedir(d);
	return (0);
}

int	iter_lst(t_list **lst, t_list **new)
{
	t_list	*index;

	if (!lst || !*lst)
		return (1);
	index = *lst;
	while (index)
	{
		if (get_match_indir(*lst, new))
			return (1);
		index = index->next;
	}
	ft_lstclear(lst, del_node);
	return (0);
}

int	rec_wildcards(t_list **lst, t_list **new, int *odd)
{
	t_wildcard	*wc;

	if (!*odd && (!lst || !*lst))
		return (1);
	if (*odd && (!new || !*new))
		return (1);
	if (!*odd)
	{
		wc = (t_wildcard *)(*lst)->content;
		if (wc->suffix[0] == '\0')
			return (0);
		if (iter_lst(lst, new))
			return (1);
	}
	if (*odd)
	{
		wc = (t_wildcard *)(*new)->content;
		if (wc->suffix[0] == '\0')
			return (0);
		if (iter_lst(new, lst))
			return (1);
	}
	*odd = !(*odd);
	return (rec_wildcards(new, lst, odd));
}

t_list	*wildcards(char *line)
{
	t_wildcard		*mywc;
	t_list		**lst_match;
	t_list		**lst_match2;
	int			odd;

	if (ft_strchr(line, '*') == NULL)
		return (ft_lstnew(line));
	mywc = init_wc();
	lst_match = ft_calloc(1, sizeof(t_list *));
	lst_match2 = ft_calloc(1, sizeof(t_list *));
	if (!lst_match || !lst_match2)
		return (NULL);
	if (update_wildcard(mywc, line))
		return (NULL);
	ft_lstadd_back(lst_match, ft_lstnew(mywc));
	odd = 0;
	rec_wildcards(lst_match, lst_match2, &odd);
	if (odd)
		return (*lst_match2);
	else
		return (*lst_match);
}