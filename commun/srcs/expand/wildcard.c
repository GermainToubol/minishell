/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 15:56:41 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/20 02:32:21 by fmauguin         ###   ########.fr       */
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

t_list	*wildcards(char *line)
{
	t_wildcard	*mywc;
	t_list		**lst_odd;
	t_list		**lst_even;
	int			odd;

	if (ft_strchr(line, '*') == NULL)
		return (NULL);
	mywc = init_wc();
	lst_odd = ft_calloc(1, sizeof(t_list *));
	lst_even = ft_calloc(1, sizeof(t_list *));
	if (!lst_odd || !lst_even)
		return (NULL);
	if (update_wildcard(mywc, line))
		return (NULL);
	ft_lstadd_back(lst_odd, ft_lstnew(mywc));
	odd = 0;
	rec_wildcards(lst_odd, lst_even, &odd);
	if (odd)
		return (*lst_even);
	else
		return (*lst_odd);
}
