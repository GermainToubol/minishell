/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 15:56:41 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/20 19:33:40 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "utils.h"
#include <unistd.h>

static int	fill_wc2(t_wildcard *mywc, char *line, size_t	i)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = ft_substr(line, 0, i);
	if (!tmp2)
		return (display_error("Error allocation\n", 0), 1);
	tmp = ft_strjoin(mywc->prefix, tmp2);
	if (!tmp)
		return (display_error("Error allocation\n", 0), 1);
	free(tmp2);
	free(mywc->prefix);
	mywc->prefix = tmp;
	if (!mywc->prefix)
		return (display_error("Error allocation\n", 0), 1);
	return (0);
}

static int	fill_wc(t_wildcard *mywc, char *line, size_t	i)
{
	if (fill_wc2(mywc, line, i))
		return (1);
	if (line[i])
	{
		while (line[i + 1] == '*')
			i++;
		free(mywc->suffix);
		if (!line[i])
			i--;
		mywc->suffix = ft_strdup(&line[i]);
		if (!mywc->suffix)
			return (display_error("Error allocation\n", 0), 1);
	}
	return (0);
}

static int	update_dir_path(t_wildcard *mywc, char *line, size_t i)
{
	char	*tmp;
	char	*tmp2;

	if (line[0] == '/')
		tmp2 = ft_substr(line, 1, i);
	else
		tmp2 = ft_substr(line, 0, i);
	if (!tmp2)
		return (display_error("Error allocation\n", 0), 1);
	if (mywc->dir_path[ft_strlen(mywc->dir_path) - 1] == '/')
		tmp = ft_strjoin(mywc->dir_path, tmp2);
	else
		tmp = ft_join3(mywc->dir_path, "/", tmp2);
	if (!tmp)
		return (display_error("Error allocation\n", 0), 1);
	free(mywc->dir_path);
	free(tmp2);
	mywc->dir_path = tmp;
	if (!mywc->dir_path)
		return (display_error("Error allocation\n", 0), 1);
	return (0);
}

int	update_wildcard(t_wildcard *mywc, char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && line[i] != '*')
	{
		if (line[i] == '/')
		{
			if (update_dir_path(mywc, line, i))
				return (1);
			return (update_wildcard(mywc, &line[i + 1]));
		}
		i++;
	}
	if (fill_wc(mywc, line, i))
		return (1);
	return (0);
}

t_list	*wildcards(char *line)
{
	t_wildcard	*mywc;
	t_list		**lst_odd;
	t_list		**lst_even;
	t_list		*ret;

	if (ft_strchr(line, '*') == NULL)
		return (NULL);
	mywc = init_wc(line);
	lst_odd = ft_calloc(1, sizeof(t_list *));
	lst_even = ft_calloc(1, sizeof(t_list *));
	if (!lst_odd || !lst_even)
		return (NULL);
	if (update_wildcard(mywc, line))
		return (NULL);
	ft_lstadd_back(lst_odd, ft_lstnew(mywc));
	if (rec_wildcards(lst_odd, lst_even))
		return (NULL);
	if (!lst_even || !*lst_even)
		ret = *lst_odd;
	else
		ret = *lst_even;
	free(lst_even);
	free(lst_odd);
	return (ret);
}
