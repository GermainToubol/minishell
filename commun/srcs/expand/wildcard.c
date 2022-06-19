/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 15:56:41 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/20 00:59:18 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "utils.h"
#include <unistd.h>

void	printf_wc(t_wildcard *mywc)
{
	if (mywc->dir_path)
		ft_printf("\tpath: %s\n", mywc->dir_path);
	if (mywc->prefix)
		ft_printf("\tprefix: %s\n", mywc->prefix);
	if (mywc->suffix)
		ft_printf("\tsuffix: %s\n\n", mywc->suffix);
}

int	update_wildcard(t_wildcard *mywc, char *line, char *found)
{
	size_t	i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	if (found)
	{
		free(mywc->prefix);
		mywc->prefix = ft_strdup(found);
	}
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
		mywc->suffix = ft_strdup(&line[i]);
	}
	return (0);
}

int	check_match_dir(t_wildcard *mywc, t_list **lst_match)
{
	char	*tmp;

	if (!lst_match || !*lst_match)
		return (1);
	tmp = ft_strchr(mywc->suffix, '*');
	while (tmp)
	{
		printf_wc(mywc);
		if (update_wildcard(mywc, mywc->suffix, NULL))
			return (1);
		tmp = mywc->suffix;
	}
	ft_list_remove_if(lst_match, mywc->suffix, strncmp_sep, del_node);
	ft_lstiter(*lst_match, print_lst2);
	return (0);
}

t_wildcard	*new_wc(t_wildcard *mywc, char *found, size_t i, size_t i2)
{
	t_wildcard	*new;

	new = ft_calloc(1, sizeof(t_wildcard));
	if (!new)
		return (display_error("Error allocation\n", 0), NULL);
	new->dir_path = ft_strdup(mywc->dir_path);
	new->prefix = ft_substr(found, 0, i2);
	if (mywc->suffix[i] == '*')
		new->suffix = ft_strdup(&mywc->suffix[i + 1]);
	else
		new->suffix = ft_strdup("");
	if (!new->dir_path || !new->prefix || !new->suffix)
		return (display_error("Error allocation\n", 0), NULL);
	return (new);
}

t_wildcard	*prefix_suffix(t_wildcard *mywc, char *found)
{
	size_t		i;
	size_t		i2;

	i = 0;
	i2 = 0;
	while (mywc->prefix[i] && found[i2] && mywc->prefix[i] == found[i2])
	{
		i++;
		i2++;
	}
	if (mywc->prefix[i] != found[i2] && mywc->prefix[i])
		return (NULL);
	while (found[i2])
	{
		i = 0;
		while (found[i2 + i] && mywc->suffix[i]
				&& mywc->suffix[i] == found[i2 + i])
			i++;
		if (mywc->suffix[i] == '*' || mywc->suffix[i] == '\0')
			return (new_wc(mywc, found, i, i2));
		i2++;
	}
	return (NULL);
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

t_wildcard	*init_wc(void)
{
	t_wildcard	*new;
	char 		cwd_dir[DIR_BUFFER];

	new = ft_calloc(1, sizeof(t_wildcard *));
	if (!new)
		return (display_error("Error allocation\n", 0), NULL);
	new->dir_path = ft_strdup(getcwd(cwd_dir, DIR_BUFFER));
	new->suffix = ft_strdup("");
	new->prefix = ft_strdup("");
	if (!new->dir_path || !new->prefix || !new->suffix)
		return (display_error("Error allocation\n", 0), NULL);
	return (new);
}

t_list	*wildcards(char *line)
{
	t_wildcard		*mywc;
	t_list		**lst_match;
	t_list		**lst_match2;
	char			*found;

	if (ft_strchr(line, '*') == NULL)
		return (ft_lstnew(line));
	mywc = init_wc();
	found = NULL;
	lst_match = ft_calloc(1, sizeof(t_list *));
	lst_match2 = ft_calloc(1, sizeof(t_list *));
	if (!lst_match || !lst_match2)
		return (NULL);
	if (update_wildcard(mywc, line, found))
		return (NULL);
	ft_lstadd_back(lst_match2, ft_lstnew(mywc));
	if (get_match_indir(*lst_match2, lst_match))
		return (NULL);
	ft_lstiter(*lst_match, print_lst2);
	return (*lst_match);
}